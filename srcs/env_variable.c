/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/15 16:31:07 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			push_env_variable_list(t_env_variable *env_variables,
		char *name, char *value)
{
	t_env_variable	*tmp;
	t_env_variable	*new;

	if ((tmp = get_env_variable_if_exist(env_variables, name)) != NULL)
	{
		tmp->content = value;
		return ;
	}
	if (!(new = malloc(sizeof(t_env_variable))))
		return ;
	tmp = env_variables;
	while (tmp)
	{
		if (!tmp->next)
		{
			tmp->next = new;
			new->name = name;
			new->content = value;
			new->next = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

void			init_env_variables(t_env_variable
*env_variables, t_env *shell_env, char **env)
{
	int		i;
	int		j;

	env_variables->name = "PATH";
	env_variables->content = "/Users";
	env_variables->next = NULL;
	shell_env->env_variables = env_variables;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		push_env_variable_list(env_variables, get_arg_quotes(env[i], '='),
				get_arg_quotes(env[i] + j + 1, 0));
		i++;
	}
}
