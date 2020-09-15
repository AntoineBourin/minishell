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

void		exec_cmd_redirection(t_cmdlist **list, t_env *env)
{
	t_cmdlist *list_2;

	list_2 = *list;
	while (list_2->fd_out)
	{
		exec_cmd_redirection_list(list_2->fd_in, list_2, env);
		list_2->fd_out = list_2->fd_out->next;
	}
}

void		ft_pipe_norm1(int *fd, t_env *env)
{
	if (env->ope_type == 1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	else if (env->ope_type > 1 && env->ope_type != -1)
	{
		dup2(env->ope_type, 1);
		close(env->ope_type);
		dup2(-1, 1);
	}
	else
		dup2(-1, 1);
}

int			ft_pipe(char *str, t_env *env, int *fd, int check)
{
	static int	fd_in;
	pid_t		prog_id;

	if (!check)
		fd_in = 0;
	fd_in = (!fd_in) ? 0 : fd_in;
	prog_id = fork();
	if (prog_id == 0)
	{
		dup2(fd_in, 0);
		ft_pipe_norm1(fd, env);
		command_read(str, env);
		exit(env->last_program_return);
		fd_in = 0;
	}
	else
	{
		wait(&prog_id);
		env->last_program_return = WEXITSTATUS(prog_id);
		close(fd[1]);
		fd_in = fd[0];
	}
	return (1);
}

void		pipe_select_norm2(t_env *env, char *str, int fd_out)
{
	if (check_if_char_in_str_is_in_str2("|", str))
		env->ope_type = 1;
	else
	{
		if (fd_out == 1)
			env->ope_type = 0;
		else
			env->ope_type = fd_out;
	}
}

void		pipe_select_norm1(t_env *env, char *str, int fd_out)
{
	if (check_if_char_in_str_is_in_str2("|", str))
		env->ope_type = 1;
	else
	{
		if (fd_out == 1)
			env->ope_type = 0;
		else
			env->ope_type = fd_out;
	}
}
