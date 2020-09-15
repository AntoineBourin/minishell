/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/04 11:01:47 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env_list_norm(char *result, t_env *env)
{
	ft_putstr_fd(result, 1);
	env->last_program_return = 0;
}

char	*display_env_list(t_env *env)
{
	t_env_variable	*variables;
	char			*result;
	char			*tmp;

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
	display_env_list_norm(result, env);
	return (NULL);
}
