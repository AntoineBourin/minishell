/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_read_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/10/01 18:26:03 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		start_read_command(char *buff, t_env *env)
{
	char	**cmd;
	int		i;

	i = 0;
	if (!ft_error(buff, env))
	{
		free(buff);
		return ;
	}
	cmd = split_modif(buff);
	free(buff);
	env->last_program_return = 0;
	while (cmd[i])
	{
		execute_and_sort_cmd(cmd[i], env);
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void		ft_signal(int i)
{
	if (i == 1)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, ft_sigint);
	}
	else if (i == 2)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
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
	ft_signal(2);
	while ((bytes_readen = read(0, buff, 4095)) > 0)
	{
		buff[bytes_readen - 1] = '\0';
		ft_signal(0);
		start_read_command(env_translator(buff, env), env);
		print_prompt(0);
		ft_signal(2);
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
