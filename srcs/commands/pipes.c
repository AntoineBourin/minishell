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
	int			out;

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
		else if (env->ope_type > 1 && env->ope_type != -1)
		{
			dup2(env->ope_type, 1);
			close(env->ope_type);
			dup2(-1, 1);
		}
		else
			dup2(-1, 1);
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


int execute_pipes_command(t_list *commands, t_env *env, char *command, char *piped)
{
	
	int i;
	int j;
	char *copy;
	int	fd[2];
	int	fd_red;

	i = 0;
	j = 0;
	if (!piped || !command)
		return (1);
	copy = malloc(ft_strlen(piped) + 5);
	(void)command;
	env->ope_type = 0;
	fd_red = -42;

	if ((i = open(command, O_WRONLY, 0666)) > 0)
	{
		ft_strcpy_s("cat ", command, copy);
		close(i);
	}
	else
		copy[0] = '\0';
	i = 0;
	while (piped[i])
	{
		j = 0;
		if (copy[0] == '\0')
		{
			env->ope_type = 0;
			fd_red = -42;
			if (piped[i] == '|')
				i++;
			while (piped[i] && piped[i] != '|' && piped[i] != '<')
			{
				if (piped[i] == '>' && piped[i + 1] != '>')
					fd_red = open(red_name(piped + i + 1), O_WRONLY | O_CREAT | O_TRUNC, 0666);
				else if (piped[i] == '>' && piped[i + 1] == '>')
					fd_red = open(red_name(piped + i + 2), O_WRONLY | O_CREAT | O_APPEND, 0666);
				if (piped[i] == '>')
				{
					if (piped[i] == '>' && piped[i + 1] == '>')
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
		}
		else
		{
			while (piped[i] && piped[i] != '|')
				i++;
			j = ft_strlen(copy);
		}
		pipe(fd);
		if (fd_red == -1)
		{
			free(copy);
			return (i);
		}
		if (fd_red != -42 && fd_red != 0)
			env->ope_type = fd_red;
		else if (piped[i] == '|' && env->ope_type != fd_red)
			env->ope_type = 1;			
		copy[j] = '\0';
		if (copy)
			run_pipe(commands, env, copy, fd);
		copy[0] = '\0';
		if (env->ope_type > 1)
		{
			free(copy);
			return (i + 1);
		}
	}
	free(copy);
	return (i - 1);
}
