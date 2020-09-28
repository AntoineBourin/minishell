/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/13 17:03:25 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_and_check(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			exit(255);
		i++;
	}
	exit(ft_atoi(str));
}

void	ft_exit(t_env *env)
{
	if (env->ac[1] != '\0' && env->ac[2] != '\0')
	{
		ft_putstr_fd("./Minishell: exit: too many arguments\n", 1);
		env->last_program_return = 1;
	}
	else if (env->ac[1] != '\0')
		ft_exit_and_check(env->ac[1]);
	else
		exit(env->last_program_return);
}
