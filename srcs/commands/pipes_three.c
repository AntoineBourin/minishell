/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:46:12 by abourin           #+#    #+#             */
/*   Updated: 2020/02/29 16:46:28 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
