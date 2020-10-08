/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/10/03 17:32:21 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_variable		*f_lstlast(t_env_variable *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void				ft_print_declare_env(t_env *env)
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

char				*ft_print_env(t_env *env)
{
	t_env_variable	*print;
	char			**tmp;
	int				i;

	i = 0;
	tmp = list_to_tab(env->env_variables);
	tmp = in_order(tmp);
	while (tmp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	ft_free_tab(tmp);
	print = env->env_declare;
	order(print);
	while (print)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(print->content, 1);
		ft_putstr_fd("\n", 1);
		print = print->next;
	}
	return (NULL);
}

int					ft_content_exist(t_env *env, char *str)
{
	t_env_variable	*print;

	print = env->env_declare;
	while (print)
	{
		if (ft_strncmp(str, print->content, ft_strlen(str)) == 0)
			return (1);
		print = print->next;
	}
	return (0);
}

char				*env_and_export(char *str, t_env *env)
{
	t_env_variable	*new;
	char			**tab;
	int				i;

	i = 0;
	tab = ft_split(str, ' ');
	if (!tab[i])
		ft_print_env(env);
	while (tab[i])
	{
		if (!(new = malloc(sizeof(t_env_variable))))
			return (NULL);
		new->content = ft_strdup(tab[i]);
		new->next = NULL;
		if (!(env->env_declare))
			env->env_declare = new;
		else
		{
			if (ft_content_exist(env, tab[i]) == 0)
				add_back(&env->env_declare, new);
		}
		i++;
	}
	ft_free_tab(tab);
	return (NULL);
}
