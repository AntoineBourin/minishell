/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/29 01:41:56 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_variable	*f_lstlast(t_env_variable *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void			ft_print_declare_env(t_env *env)
{
	t_env_variable *print;

	print = env->env_declare;
	while (print)
	{
		ft_putstr_fd(print->content, 1);
		ft_putstr_fd("\n", 1);
		print = print->next;
	}
}

char			*ft_print_env(t_env *env)
{
	t_env_variable *print;

	print = env->env_variables;
	while (print)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(print->name, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(print->content, 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
		print = print->next;
	}
	print = env->env_declare;
	while (print)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(print->content, 1);
		ft_putstr_fd("\n", 1);
		print = print->next;
	}
	return (NULL);
}

int				ft_content_exist(t_env *env, char *str)
{
	t_env_variable *print;

	print = env->env_declare;
	while (print)
	{
		if (ft_strncmp(str, print->content, ft_strlen(str)) == 0)
			return (1);
		print = print->next;
	}
	return (0);
}

char			*env_and_export(char *str, t_env *env)
{
	t_env_variable *new;
	t_env_variable *tmp;

	tmp = NULL;
	new = malloc(sizeof(t_env_variable));
	new->content = str;
	new->next = NULL;
	if (!(env->env_declare))
	{
		env->env_declare = new;
	}
	else
	{
		if (ft_content_exist(env, str) == 0)
		{
			tmp = f_lstlast(env->env_declare);
			tmp->next = new;
		}
	}
	return (NULL);
}
