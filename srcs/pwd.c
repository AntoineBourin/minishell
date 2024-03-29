/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/10/02 01:56:58 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_env *env, char *args)
{
	int i;

	i = 0;
	while (args[i] && args[i] != ' ')
		i++;
	while (args[i])
	{
		if (args[i] != ' ')
		{
			ft_putstr_fd("pwd: too many arguments\n", 1);
			return ;
		}
		i++;
	}
	ft_putstr_fd(env->curr_path, 1);
	ft_putchar_fd('\n', 1);
	env->last_program_return = 0;
}
