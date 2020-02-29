/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:24:08 by abourin           #+#    #+#             */
/*   Updated: 2020/02/29 10:46:05 by nveron           ###   ########.fr       */
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
	int			out;

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

int		execute_pipe_norm3(char *piped, char *copy, int *j, int *i)
{
	if (piped[(*i)] == '>')
	{
		if (piped[(*i)] == '>' && piped[(*i) + 1] == '>')
			(*i)++;
		return (1);
	}
	else
	{
		copy[(*j)] = piped[(*i)];
		(*j)++;
		(*i)++;
	}
	return (0);
}

int		execute_pipe_norm4(t_env *env, char **copy, int *fd, t_list *commands)
{
	if ((*copy))
		run_pipe(commands, env, (*copy), fd);
	(*copy)[0] = '\0';
	if (env->ope_type > 1)
	{
		free((*copy));
		return (1);
	}
	return (0);
}

void	execute_pipe_norm5(t_env *env, int *fd_red, int *i, char *piped)
{
	env->ope_type = 0;
	(*fd_red) = -42;
	if (piped[(*i)] == '|')
		(*i)++;
}

int		execute_pipe_norm6(int fd_red, char **copy)
{
	if (fd_red == -1)
	{
		free((*copy));
		return (1);
	}
	return (0);
}

void	execute_pipe_norm7(int fd_red, t_env *env, char *piped, int i)
{
	if (fd_red != -42 && fd_red != 0)
		env->ope_type = fd_red;
	else if (piped[i] == '|' && env->ope_type != fd_red)
		env->ope_type = 1;
}

void	execute_pipe_norm8(int *fd_red, char *piped, int i)
{
	if (piped[i] == '>' && piped[i + 1] != '>')
		(*fd_red) = open(red_name(piped + i + 1),
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (piped[i] == '>' && piped[i + 1] == '>')
		(*fd_red) = open(red_name(piped + i + 2),
				O_WRONLY | O_CREAT | O_APPEND, 0666);
}

void	execute_pipe_norm9(t_env *env, int *fd_red, char *piped, char *copy)
{
	execute_pipe_norm5(env, &(*fd_red), &(env->i), piped);
	while (piped[env->i] && piped[env->i] != '|' && piped[env->i] != '<')
	{
		execute_pipe_norm8(&(*fd_red), piped, env->i);
		if (execute_pipe_norm3(piped, copy, &(env->j), &(env->i)))
			break ;
	}
}

int		execute_pipe_norm10(char **copy, t_env *env)
{
	if ((*copy))
		free((*copy));
	return (env->i - 1);
}

int		execute_pipes_command(t_list *commands, t_env *env,
		char *command, char *piped)
{
	int		fd[2];
	int		fd_red;
	char	*copy;

	(void)command;
	if (!piped || !command || !(copy = malloc(ft_strlen(piped) + 5)))
		return (1);
	execute_pipe_norm1(&copy, command, env, &fd_red);
	env->i = 0;
	while (piped[env->i])
	{
		env->j = 0;
		if (copy[0] == '\0')
			execute_pipe_norm9(env, &fd_red, piped, copy);
		else
			execute_pipe_norm2(piped, &(env->i), &(env->j), copy);
		pipe(fd);
		if (execute_pipe_norm6(fd_red, &copy) > 0)
			return (env->i);
		execute_pipe_norm7(fd_red, env, piped, env->i);
		copy[env->j] = '\0';
		if (execute_pipe_norm4(env, &copy, fd, commands) > 0)
			return (env->i + 1);
	}
	return (execute_pipe_norm10(&copy, env));
}
