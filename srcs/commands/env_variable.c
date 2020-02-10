/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:40:31 by abourin           #+#    #+#             */
/*   Updated: 2020/02/10 17:14:34 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_variable	*get_env_variable_if_exist(t_env_variable *env_variables,
							char *name)
{
	while (env_variables)
	{
		if (env_variables->name
			&& ft_strncmp(env_variables->name, name, ft_strlen(name)) == 0)
			return (env_variables);
		env_variables = env_variables->next;
	}
	return (NULL);
}

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

char		*display_env_list(t_env *env)
{
	t_env_variable	*variables;
	char			*result;
	char			*tmp;

	env->check = 42;
	if (!(result = malloc(sizeof(char) * 1)))
		return (NULL);
	result[0] = '\0';
	variables = env->env_variables;
	while (variables)
	{
		if (variables->name && variables->content)
		{
			tmp = ft_strjoin(result, variables->name);
			free(result);
			result = ft_strjoin(tmp, "=");
			free(tmp);
			tmp = ft_strjoin(result, variables->content);
			free(result);
			result = ft_strjoin(tmp, "\n");
			free(tmp);
		}
		variables = variables->next;
	}
	return (result);
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
}
