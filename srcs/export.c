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

int				contain_spaces(char *env_name)
{
	int		i;
	int		spaced;

	i = 0;
	spaced = 0;
	while (env_name[i] && env_name[i] != '=')
	{
		if (env_name[i] == ' ')
			spaced = 1;
		i++;
	}
	if (spaced == 1)
		env_name[i] = '\0';
	return (spaced);
}

void			remove_quote_arg2(int *check34, int *check39, int *i, char *str)
{
	(*i) = 0;
	(*check34) = 0;
	(*check39) = 0;
	while (str[(*i)])
	{
		if (str[(*i)] == 92)
		{
			(*i)++;
			if (str[(*i)])
				(*i)++;
			if (!(str[(*i)]))
				break ;
		}
		if (str[(*i)] == 34)
			(*check34)++;
		if (str[(*i)] == 39)
			(*check39)++;
		(*i)++;
	}
	(*i) = 0;
	if ((*check34) % 2 != 0)
		(*check34)--;
	if ((*check39) % 2 != 0)
		(*check39)--;
}

char			*remove_quote_arg(char *str)
{
	t_quote q;

	if (!(q.copy = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	remove_quote_arg2(&(q.check34), &(q.check39), &(q.i), str);
	q.j = 0;
	while (str[q.i])
	{
		if ((str[q.i] == 39 && q.check39 > 0)
				|| (str[q.i] == 34 && q.check34 > 0))
		{
			q.check34 = str[q.i] == 34 ? q.check34 - 1 : q.check34;
			q.check39 = str[q.i] == 39 ? q.check39 - 1 : q.check39;
			(q.i)++;
		}
		else
		{
			(q.copy)[q.j] = str[q.i];
			(q.j)++;
			(q.i)++;
		}
	}
	(q.copy)[q.j] = '\0';
	return ((q.copy));
}

char			*export_env(t_env *env, char *args)
{
	char	*env_group;
	int		i;
	char	*env_name;
	char	*env_value;

	i = 0;
	env_group = args + 6;
	if (env_group[0] == ' ')
		env_group = args + 7;
	if (env_group[0] == '\0')
		return (ft_print_env(env));
	while (env_group[i] && env_group[i] != '=')
		i++;
	if ((env_group + i)[0] == '\0')
		return (env_and_export(env_group, env));
	if (contain_spaces(env_group) == 1)
	{
		printf_error("export", 0, env_group, "not valid in this context");
		return (NULL);
	}
	env_name = get_arg_quotes(env_group, '=');
	env_value = env_group + i + 1;
	push_env_variable_list(env->env_variables, env_name, env_value);
	env->last_program_return = 0;
	return (NULL);
}
