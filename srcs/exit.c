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

void	ft_exit(t_env *env)
{
	if (env->ac[1] != '\0')
		exit(ft_atoi(env->ac[1]));
	else
		exit(env->last_program_return);
}
