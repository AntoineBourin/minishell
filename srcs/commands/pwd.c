/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 11:15:41 by abourin           #+#    #+#             */
/*   Updated: 2020/02/05 11:25:01 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pwd(t_env *env, char *args)
{
	int i;

	i = 0;
	args += 3;
	while (args[i])
	{
		if (args[i] != ' ')
			return ("pwd: too many arguments");
			i++;
	}
	return (env->curr_path);
}
