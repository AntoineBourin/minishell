/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:43:31 by abourin           #+#    #+#             */
/*   Updated: 2020/02/29 16:43:53 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pipe2(t_env *env, int *fd)
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

int		run_pipe(t_list *commands, t_env *env, char *str, int *fd)
{
	static int	fd_in;
	pid_t		prog_id;

	if (!fd)
		return (0);
	fd_in = (!fd_in) ? 0 : fd_in;
	prog_id = fork();
	if (prog_id == 0)
	{
		dup2(fd_in, 0);
		run_pipe2(env, fd);
		if (env->ope_type != -1)
			red_cut(commands, env, str);
		exit(42);
		fd_in = 0;
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		fd_in = fd[0];
	}
	return (1);
}

void	ft_strcpy_s(const char *src, const char *src2, char *dest)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!src || !dest || !src2)
		return ;
	while (src[i] && dest[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (src2[j] && dest[i + j])
	{
		dest[i + j] = src2[j];
		j++;
	}
	dest[i + j] = '\0';
}

void	execute_pipe_norm1(char **copy, char *command, t_env *env, int *fd_red)
{
	int fd;

	fd = 0;
	if ((fd = open(command, O_WRONLY, 0666)) > 0)
	{
		ft_strcpy_s("cat ", command, (*copy));
		close(fd);
	}
	else
		(*copy)[0] = '\0';
	env->ope_type = 0;
	(*fd_red) = -42;
}

void	execute_pipe_norm2(char *piped, int *i, int *j, char *copy)
{
	while (piped[(*i)] && piped[(*i)] != '|')
		(*i)++;
	(*j) = ft_strlen(copy);
}