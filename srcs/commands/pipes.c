/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:24:08 by abourin           #+#    #+#             */
/*   Updated: 2020/02/14 14:59:27 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_containing_pipes(char *piped)
{
	int		i;
	int		in_args;

	i = 0;
	in_args = -1;
	while (piped[i])
	{
		if (piped[i] == '|' && in_args == -1)
			return (i);
		if (piped[i] == '"')
			in_args *= -1;
		i++;
	}
	return (-1);
}

void	ft_split_first_pipe(t_list *commands, t_env *env, char *first,
						char *command, char *piped)
{
	char	*cpy;

	cpy = ft_strdup(piped + is_containing_pipes(piped) + 1);
	piped[is_containing_pipes(piped)] = '\0';
	execute_pipes_command(commands, env, NULL, piped + 1, cpy);
}

void	execute_pipes_command(t_list *commands, t_env *env, char *first,
						char *command, char *piped)
{
	int		pipefd[2];
	int		pid;
	int		oldfd;
	int		t;
	int		pipefd2[2];
	char	*result;
	int		z;
	char	buffer[4096];

	// pipefd 1 == write
	// pipefd 0 == read
	//printf("first <%s>, command <%s>, piped <%s>\n", first, command, piped);
	if (pipe(pipefd) == -1)
		printf("ERROR PIPE\n");
	if (pipe(pipefd2) == -1)
		printf("ERROR PIPE\n");
	if ((pid = fork()) == -1)
		printf("ERROR FORK\n");
	if (pid == 0)
	{
		close(pipefd[0]); // write side
		dup2(pipefd[1], 1);
		if (env->buff)
		{
			// take standard input of last process
		}
		result = red_cut(commands, env, first ? first : command);
		if (result)
			ft_putstr_fd(result, 1);
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		wait(NULL);
		close(pipefd[1]); // read side
		dup2(pipefd[0], 0);
		if (is_containing_pipes(piped) != -1)
		{
			t = read(pipefd[0], buffer, 4095);
			buffer[t] = 0;
			env->buff = buffer;
			ft_split_first_pipe(commands, env, first, command, piped);
			return ;
		}
		result = red_cut(commands, env, piped + 1);
		close(pipefd[0]);
		pid = fork();
		if (pid == 0)
			exit(0);
	}
}
