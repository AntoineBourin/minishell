/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:40:31 by abourin           #+#    #+#             */
/*   Updated: 2020/02/05 16:37:28 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_env_variable_list(t_env_variable *env_variables, char *name,
						char *value)
{
	t_env_variable	*tmp;
	t_env_variable	*new;

	new = malloc(sizeof(t_env_variable));
	tmp = env_variables;
	while (tmp)
	{
		if (!tmp->next)
		{
			tmp->next = new;
			new->name = name;
			printf("%s\n", name);
			printf("%s\n", value);
			new->content = value;
			new->next = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

char	*display_env_list(t_env *env)
{
	t_env_variable	*variables;

	variables = env->env_variables;
	// TODO:: No printf and return list with char *
	while (variables)
	{
		if (variables->name && variables->content)
			printf("%s=%s\n", variables->name, variables->content);
		variables = variables->next;
	}
	return (NULL);
}

void	export_env(t_env *env, char *cmd, char *args)
{
	char	*env_group;
	int		i;
	char	*env_name;
	char	*env_value;

	i = 0;
	env_group = args + 7;
	while (env_group[i] && env_group[i] != '=')
		i++;
	env_name = get_arg_quotes(env_group, '=');
	env_value = get_arg_quotes(env_group + i + 1, 0);
	push_env_variable_list(env->env_variables, env_name, env_value);
	display_env_list(env);
}
