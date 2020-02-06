/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:10:39 by abourin           #+#    #+#             */
/*   Updated: 2020/02/06 12:31:29 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		remove_env_variable(t_env_variable **env_variables, char *name)
{
	t_env_variable	*tmp;
	t_env_variable	*prec;

	if (!env_variables)
		return ;
	tmp = *env_variables;
	while (tmp)
	{
		if (tmp->name && ft_strncmp(tmp->name, name, 4096) == 0)
		{
			if (prec)
				prec->next = tmp->next;
			else
			{
				env_variables = &(tmp->next);
			}
			free(tmp);
			tmp = NULL;
		}
		prec = tmp;
		if (tmp)
			tmp = tmp->next;
	}
}

void		unset(t_env *env, char *cmd, char *args)
{
	char	*env_group;
	char	*env_name;

	env_group = args + 6;
	env_name = get_arg_quotes(env_group, 0);
	if (get_env_variable_if_exist(env->env_variables, env_name) == NULL)
		return ;
	remove_env_variable(&(env->env_variables), env_name);
}
