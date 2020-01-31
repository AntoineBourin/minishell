/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:06:25 by abourin           #+#    #+#             */
/*   Updated: 2020/01/31 15:08:38 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_env_path(t_env *env)
{
	char	*curr_path;

	if (!(curr_path = malloc(sizeof(char) * 2)))
		return (0);
	curr_path[0] = '~';
	curr_path[1] = '\0';
	env->curr_path = curr_path;
	return (1);
}

static void	print_curr_path(t_env *env)
{
	ft_putstr_fd(env->curr_path, 1);
	ft_putchar_fd(' ', 1);
}

char		*command_read(t_env *env)
{
	char	buff[4096];
	char	*result;
	int		bytes_readen;

	if (!(result = malloc(sizeof(char) * 1)))
		return (NULL);
	result[0] = '\0';
	init_env_path(env);
	print_curr_path(env);
	while ((bytes_readen = read(0, buff, 4095)) > 0)
	{
		buff[bytes_readen] = '\0';
		printf("bytes %d\n\n", bytes_readen);
		if (bytes_readen < 4095)
			print_curr_path(env);
	}
	return (result);
}
