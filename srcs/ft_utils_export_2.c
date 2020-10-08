/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_export_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 17:44:04 by cnotin            #+#    #+#             */
/*   Updated: 2020/10/04 22:17:24 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					verif_export_var(char *cmd, t_env *env, char *tot)
{
	int				i;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i] != 97 && (cmd[i] < 48 || cmd[i] > 57) &&
			(cmd[i] < 65 || cmd[i] > 90) && (cmd[i] < 97 || cmd[i] > 122))
		{
			ft_putstr_fd("export: not valid in this context: ", 1);
			ft_putstr_fd(tot, 1);
			ft_putchar_fd('\n', 1);
			env->last_program_return = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int					var_exist(t_env_variable *list, char *var)
{
	t_env_variable	*next;

	while (list)
	{
		next = list->next;
		if (!ft_memcmp(list->name, var, ft_strlen(list->name)))
			return (1);
		list = next;
	}
	return (0);
}

char				*content_exist(t_env_variable *list, char *var)
{
	t_env_variable	*next;

	while (list)
	{
		next = list->next;
		if (!ft_memcmp(list->name, var, ft_strlen(list->name)))
			return (list->content);
		list = next;
	}
	return (NULL);
}

void				push_value(t_env *env, char *env_value, char *env_group,
					char *env_name)
{
	env_value = env_group + env->l + 1;
	push_env_variable_list(env->env_variables, env_name, env_value);
	env->last_program_return = 0;
}

void				add_back(t_env_variable **alst, t_env_variable *new)
{
	t_env_variable	*newcpy;

	newcpy = *alst;
	while (newcpy->next)
		newcpy = newcpy->next;
	newcpy->next = new;
}
