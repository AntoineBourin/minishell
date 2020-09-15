/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/15 16:31:07 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_if_char_is_in_str(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char			*cut_cmd_by_arg_fill(char
*command, char **ac, char *str, int *arg_i)
{
	int i;

	i = 0;
	while (command[i] && check_if_char_is_in_str(command[i], str) != 1)
	{
		while (command[i] == 92 && command[i + 1])
			i++;
		i++;
	}
	if (!(ac[*arg_i] = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (command[i] && check_if_char_is_in_str(command[i], str) != 1)
	{
		while (command[i] == 92 && command[i + 1])
			command++;
		ac[*arg_i][i] = command[i];
		i++;
	}
	ac[*arg_i][i] = '\0';
	(*arg_i)++;
	return (command + i);
}

char			*cut_cmd_by_arg_fill_2(char
*command, char **ac, char *str, int *arg_i)
{
	int i;

	i = 0;
	while (command[i] && check_if_char_is_in_str(command[i], str) != 1)
		i++;
	if (!(ac[*arg_i] = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (command[i] && check_if_char_is_in_str(command[i], str) != 1)
	{
		ac[*arg_i][i] = command[i];
		i++;
	}
	ac[*arg_i][i] = '\0';
	(*arg_i)++;
	if (command[i])
		return (command + i + 1);
	return (command + i);
}

void			cut_cmd_by_arg(char *command, char **ac)
{
	int i;
	int arg_i;

	i = 0;
	arg_i = 0;
	while (command[i])
	{
		if (command[i] == 34 || command[i] == 39)
		{
			if (command[i] == 34)
				command = cut_cmd_by_arg_fill_2(command + 1, ac, "\"", &arg_i);
			else if (command[i] == 39)
				command = cut_cmd_by_arg_fill_2(command + 1, ac, "'", &arg_i);
			i = 0;
		}
		else
		{
			while (*command == ' ')
				command++;
			if (command[i] && command[i] != 34 && command[i] != 39)
				command = cut_cmd_by_arg_fill(command, ac, "'\" ", &arg_i);
		}
	}
	ac[arg_i] = NULL;
}

char			**get_function_args(char *command)
{
	char	**ac;

	command = place_str_at_the_begin_command(command);
	if (!(ac = malloc(sizeof(char *) * (get_nb_function_args(command) + 3))))
		return (NULL);
	ac[get_nb_function_args(command)] = NULL;
	cut_cmd_by_arg(command, ac);
	return (ac);
}
