/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:06:25 by abourin           #+#    #+#             */
/*   Updated: 2020/07/19 18:24:25 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_curr_path(t_env *env)
{
	ft_putstr_fd(env->curr_path, 1);
	ft_putstr_fd(" : ", 1);
}


void		ft_exit(int i)
{
	char *str;

	(void)i;
	str = NULL;
	str = getcwd(str, 1000000);
	write(1, "\n", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(" : ", 1);
}

void		ft_exit_2(int i)
{
	write(1, "\n", 1);
}
void		command_read(t_env *env)
{
	char	buff[4096];
	int		bytes_readen;

	bytes_readen = -1;
	signal(SIGINT, ft_exit);
	if (bytes_readen == -1)
		print_curr_path(env);
	while ((bytes_readen = read(0, buff, 4095)) > 0)
	{
		if (bytes_readen > 1 && buff[bytes_readen - 1] != '\n')
		{
			write(1, "\n", 1);
			buff[bytes_readen] = '\0';
		}
		else
			buff[bytes_readen - 1] = '\0';
		if (bytes_readen < 4095 && bytes_readen > 0)
		{
			signal(SIGINT, ft_exit_2);
			command_middleware(env, env_translator(buff, env));
			print_curr_path(env);
			signal(SIGINT, ft_exit);
		}
	}
}


void		cd_split(t_env *env, char *buff)
{
	char	*str;
	int		i;
	int		j;

	i = 2;
	j = 0;
	if ((!(str = malloc(ft_strlen(buff) * sizeof(char)))) &&
			((buff[2] != ' ') || (buff[2] != '\0')))
		return ;
	while (buff[i])
	{
		str[j] = buff[i];
		i++;
		j++;
	}
	str[j] = '\0';
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		move(NULL, 0, env);
	else
		move(str, 0, env);
	ft_free(&str);
}
