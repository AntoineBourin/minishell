/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:24:08 by abourin           #+#    #+#             */
/*   Updated: 2020/02/29 16:47:50 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
