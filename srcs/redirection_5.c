/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/10 16:42:10 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_cmd_with_fd_in(char **last_cmd, t_fdlist
*list, int fd_out, t_env *env)
{
	while (list && list->fd != 0)
	{
		redirection(*last_cmd, list->fd, fd_out, env);
		list = list->next;
	}
	free(*last_cmd);
}

void		exec_cmd_redirection_for_pipe(t_env *env, char *ref)
{
	char	*str;
	int		fd[2];

	str = NULL;
	while (*ref)
	{
		pipe(fd);
		cut_cmd_for_pipe(&str, &ref);
		if (check_str_char_in_quote("|", ref))
			ft_pipe(str, env, fd, 1);
		else
			ft_pipe(str, env, fd, 0);
		if (*ref == '|')
			ref++;
	}
}

void		redirection_sort(char *str, t_env *env)
{
	char		**ac;
	t_cmdlist	*list;

	ac = NULL;
	list = fill_list(env, ac, str);
	if (list->check_error != 1)
	{
		if (check_str_char_in_quote("|", str))
		{
			exec_cmd_redirection_for_pipe(env, str);
		}
		else
		{
			exec_cmd_redirection(&list, env);
		}
	}
	else
		env->last_program_return = 1;
}
