/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:24:08 by abourin           #+#    #+#             */
/*   Updated: 2020/02/26 11:36:42 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_pipe(t_list *commands, t_env *env, char *str, int *fd)
{
	static int	fd_in;
	pid_t		prog_id;
	int			new_fd;
	new_fd = open(".cache", O_WRONLY | O_CREAT | O_TRUNC, 0666);

	if (!fd)
		return (0);
	fd_in = (!fd_in) ? 0 : fd_in;
	prog_id = fork();
	if (prog_id == 0)
	{
		dup2(fd_in, 0);
		if(env->ope_type == 1)
		{
			dup2(fd[1], 1);
			close(fd[1]);
		}
		else if (env->ope_type > 1)
		{
			dup2(env->ope_type, 1);
			close(env->ope_type);
		}
		else
			dup2(-1, 1);
		red_cut(commands, env, str);
		exit(42);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		fd_in = fd[0];
	}
	return (1);
}

int execute_pipes_command(t_list *commands, t_env *env, char *command, char *piped)
{
	
	int i;
	int j;
	char *copy;
	int			fd[2];
	int fd_red;

	i = 0;
	j = 0;
	copy = malloc(ft_strlen(piped) + 1);
	(void)command;
	while (piped[i])
	{
		j = 0;
		fd_red = -42;
		env->ope_type = 0;
		if (piped[i] == '|')
			i++;
		//else if (piped[i] == '>' || piped[i] == '<')
		//	return (i);
		while (piped[i] && piped[i] != '|' && piped[i] != '<')
		{
			if (piped[i] == '>' && piped[i + 1] != '>')
				fd_red = open(red_name(piped + i + 1), O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else if (piped[i] == '>' && piped[i + 1] == '>')
				fd_red = open(red_name(piped + i + 2), O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (piped[i] == '>')
			{
				while (piped[i] == '>')
					i++;
				while (piped[i] && piped[i] != '|' && piped[i] != '>' && piped[i] != '<')
					i++;
				break ;
			}
			else
			{
				copy[j] = piped[i];
				j++;
				i++;
			}
		}
		pipe(fd);
		if (fd_red != -42 && fd_red != 0)
			env->ope_type = fd_red;
		else if (piped[i] == '|')
			env->ope_type = 1;			
		copy[j] = '\0';
		run_pipe(commands, env, copy, fd);
	}
	free(copy);
	return (i - 1);
}
