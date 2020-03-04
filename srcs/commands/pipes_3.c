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
