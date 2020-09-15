/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/10 16:44:47 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		start_read_command(char *buff, t_env *env)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = split_modif(buff);
	env->last_program_return = 0;
	while (cmd[i])
	{
		execute_and_sort_cmd(cmd[i], env);
		i++;
	}
}

void		ft_signal(int i)
{
	if (i)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, ft_sigint);
	}
	else
	{
		signal(SIGINT, ft_sigint_cat);
		signal(SIGQUIT, ft_sigint_cat);
	}
}

void		start_get_commmand(t_env *env)
{
	char	buff[4096];
	int		bytes_readen;

	bytes_readen = -1;
	ft_signal(1);
	while ((bytes_readen = read(0, buff, 4095)) > 0)
	{
		buff[bytes_readen - 1] = '\0';
		ft_signal(0);
		start_read_command(env_translator(buff, env), env);
		print_prompt(0);
		ft_signal(1);
	}
}

void		command_remove_quote_etc_norm1(char **str,
char *ref_str, int *presence_of_34, int *presence_of_39)
{
	while (**str == 34 && *presence_of_39 < 0)
	{
		if (((ref_str == *str || *(*str - 1) != 92)
		&& *presence_of_34 < 0) || (*presence_of_34 > 0))
		{
			(*presence_of_34) *= -1;
			(*str)++;
		}
		else
			break ;
	}
	while (**str == 39 && *presence_of_34 < 0)
	{
		if (((ref_str == *str || *(*str - 1) != 92)
		&& *presence_of_39 < 0) || (*presence_of_39 > 0))
		{
			(*presence_of_39) *= -1;
			(*str)++;
		}
		else
			break ;
	}
}

void		command_remove_quote_etc_norm2(char **str, char **buff)
{
	if (**str == 92)
	{
		(*str)++;
		**buff = **str;
		(*buff)++;
		if (**str)
			(*str)++;
	}
	else
	{
		**buff = **str;
		(*str)++;
		(*buff)++;
	}
}
