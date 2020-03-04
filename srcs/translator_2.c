/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:35:56 by abourin           #+#    #+#             */
/*   Updated: 2020/03/04 07:48:36 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_norm1(char ***res, t_comp *c1, int begin_index, char **tmp)
{
	c1->i = 0;
	c1->j = 0;
	while ((**res)[c1->i] && (int)c1->i < begin_index - 1)
	{
		(*tmp)[c1->i] = (**res)[c1->i];
		(c1->i)++;
	}
	c1->k = c1->i;
}

void	replace_env_norm2(int *length, t_env_variable *env)
{
	if (env == NULL)
		(*length) = 0;
	else
		(*length) = ft_strlen(env->content) - ft_strlen(env->name);
}
