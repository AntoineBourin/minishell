/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:24:08 by abourin           #+#    #+#             */
/*   Updated: 2020/02/12 15:13:46 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_pipe(t_list *commands, t_env *env, char *str, int *fd)
{
	static int	fd_in;
	pid_t		prog_id;

	//if (!fd)
	//	return (0);
	fd_in = (!fd_in) ? 0 : fd_in;
	prog_id = fork();
	if (prog_id == 0)
	{
		dup2(fd_in, 0);
		dup2((env->ope_type == 1) ? fd[1] : -1, 1);
		close(fd[1]);
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

	i = 0;
	j = 0;
	copy = malloc(ft_strlen(piped) + 1);
	while (piped[i])
	{
		j = 0;
		env->ope_type = 0;
		if (piped[i] == '|')
			i++;
		else if (piped[i] == '>' || piped[i] == '<')
			return (i);
		while (piped[i] && piped[i] != '|' && piped[i] != '>' && piped[i] != '<')
		{
			copy[j] = piped[i];
			j++;
			i++;
		}
		if (piped[i] == '|')
			env->ope_type = 1;
		copy[j] = '\0';
		pipe(fd);
		run_pipe(commands, env, copy, fd);
	}
	free(copy);
	return (i - 1);
}
