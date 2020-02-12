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

void	execute_pipes_command(t_list *commands, t_env *env,
						char *command, char *piped)
{
	int		pipefd[2];
	int		pid;
	int		oldfd;
	char	buffer[4096];
	int		ret;
	char	*result;

	// pipefd 1 == write
	// pipefd 0 == read
	if (pipe(pipefd) == -1)
		printf("ERROR PIPE\n");
	if ((pid = fork()) == -1)
		printf("ERROR FORK\n");
	else if (pid == 0)
	{
		oldfd = dup(1);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		result = red_cut(commands, env, command);
		if (result)
			ft_putstr_fd(result, 1);
		dup2(oldfd, 0);
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		close(pipefd[1]);
		oldfd = dup(0);
		dup2(pipefd[0], 0);
		result = red_cut(commands, env, piped + 1);
		dup2(oldfd, 0);
		close(pipefd[0]);
		pid = fork();
		if (pid == 0)
			exit(0);
	}
}
