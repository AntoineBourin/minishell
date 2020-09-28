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

int			check_str_char_in_quote(char *c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (check_if_char_is_in_str_modif(str, c, i))
			return (1);
		i++;
	}
	return (0);
}

int			length_malloc(char *str, char *c)
{
	int i;

	i = 0;
	while (str[i] && check_if_char_is_in_str_modif(str, c, i) == 0)
	{
		i++;
	}
	return (i);
}

void		cut_cmd_for_pipe(char **str, char **ref)
{
	int i;

	i = 0;
	if (*str)
	{
		free(*str);
		(*str) = NULL;
	}
	if (!((*str) = malloc(sizeof(char) * (length_malloc(*ref, "|") + 1))))
		return ;
	while ((*ref)[i] && check_if_char_is_in_str_modif(*ref, "|", i) == 0)
	{
		(*str)[i] = (*ref)[i];
		i++;
	}
	(*str)[i] = '\0';
	*ref += i;
}

void		ft_pipe_norm1(int *fd, t_env *env)
{
	if (env->ope_type == 1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	else
		dup2(-1, 1);
}

void		ft_pipe(char *str, t_env *env, int *fd, int check)
{
	static int	fd_in;
	pid_t		prog_id;

	fd_in = (!fd_in) ? 0 : fd_in;
	prog_id = fork();
	env->ope_type = check;
	if (prog_id == 0)
	{
		dup2(fd_in, 0);
		if (command_path_to_file_with_env(command_name_with_or_without_quote(
			str), env) == 0 || ft_strncmp("export", str, 7) == 0)
			ft_pipe_norm1(fd, env);
		execute_and_sort_cmd(str, env);
		exit(env->last_program_return);
	}
	else
	{
		wait(&prog_id);
		env->last_program_return = WEXITSTATUS(prog_id);
		close(fd[1]);
		fd_in = fd[0];
	}
}
