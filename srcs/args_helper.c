/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:21:08 by abourin           #+#    #+#             */
/*   Updated: 2020/02/26 11:31:00 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_nb_function_args(char *command)
{
	int		i;
	int		arg_count;

	i = 0;
	arg_count = 0;
	while (command[i])
	{
		if (command[i] == ' ')
			i++;
		else if (command[i] == '"')
		{
			arg_count++;
			i++;
			while (command[i] && command[i] != '"')
				i++;
		}
		else
		{
			arg_count++;
			while (command[i] && command[i] != ' ')
				i++;
		}
	}
	return (arg_count);
}

char	*fill_arg_value(char *arg_begin, int is_quoted)
{
	int		len;
	char	*arg;
	int		i;

	len = 0;
	while (arg_begin[len])
	{
		if (arg_begin[len] == '"' && is_quoted)
			break ;
		else if (arg_begin[len] == ' ' && !is_quoted)
			break ;
		len++;
	}
	if (!(arg = malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (arg_begin[i] && i < len)
	{
		arg[i] = arg_begin[i];
		i++;
	}
	arg[i] = '\0';
	return (arg);
}

char	*get_function_args2(int *i, char *command, int *arg_i)
{
	int j;

	j = *i;
	(*arg_i)++;
	(*i)++;
	while (command[(*i)] && command[(*i)] != '"')
		(*i)++;
	while (command[(*i)] && command[(*i)] == '"')
		(*i)++;
	return (fill_arg_value(command + j + 1, 1));
}

char	**get_function_args(char *command)
{
	char	**ac;
	int		i;
	int		arg_i;

	arg_i = 0;
	i = 0;
	if (!(ac = malloc(sizeof(char *) * (get_nb_function_args(command) + 1))))
		return (NULL);
	ac[get_nb_function_args(command)] = NULL;
	while (command[i])
	{
		if (command[i] == ' ')
			i++;
		else if (command[i] == '"')
			ac[arg_i] = get_function_args2(&i, command, &arg_i);
		else
		{
			ac[arg_i] = fill_arg_value(command + i, 0);
			arg_i++;
			while (command[i] && command[i] != ' ')
				i++;
		}
	}
	ac[arg_i] = NULL;
	return (ac);
}

char	*get_arg_quotes(char *arg, char charset)
{
	int		is_quoted;
	int		i;

	i = 0;
	if (arg[0] && arg[0] == '"')
		is_quoted = 1;
	if (arg[0] && arg[0] == '"')
		i++;
	else
		is_quoted = 0;
	while (arg[i])
	{
		if ((arg[i] == charset) || (arg[i] == ' ' && !is_quoted))
		{
			arg[i] = '\0';
			return (arg);
		}
		if (arg[i] == '"' && is_quoted)
		{
			arg[i] = '\0';
			return (arg + 1);
		}
		i++;
	}
	return (arg);
}
