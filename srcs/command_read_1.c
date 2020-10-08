/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_read_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/10/01 13:01:54 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_command_path_to_file(char *path)
{
	struct stat		sb;
	int				res;

	res = stat(path, &sb);
	return (S_ISDIR(sb.st_mode) ? 2 : res);
}

int				get_nb_function_args(char *command)
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

char			*fill_arg_value(char *arg_begin, int is_quoted)
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

char			**exec_binary_norm(char **t)
{
	if (!(t = malloc(sizeof(char *) * 2)))
		return (NULL);
	t[0] = ft_strdup("TERM=xterm");
	t[1] = NULL;
	return (t);
}

char			*get_function_args2(int *i, char *command, int *arg_i)
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
