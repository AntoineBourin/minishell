/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:21:44 by cnotin            #+#    #+#             */
/*   Updated: 2020/10/01 14:08:36 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				ft_free_tab(char **tab)
{
	int				i;

	i = 0;
	if (!tab || !tab[i])
		return ;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

char				**in_order(char **tab)
{
	char			*tmp;
	int				i;
	int				j;

	i = 0;
	while (tab[i])
		i++;
	j = i;
	i = 0;
	while (i < j - 1)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	return (tab);
}

char				**list_to_tab(t_env_variable *env)
{
	char			**tab;
	char			*tmp;
	int				i;

	i = 0;
	if (!(tab = (char **)ft_calloc(sizeof(char *), ft_size(env) + 1)))
		return (NULL);
	while (env)
	{
		if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(env->name) +
			ft_strlen(env->content) + 4)))
			return (NULL);
		tmp = ft_strcpy(tmp, env->name);
		tmp = ft_strcat(tmp, "=\"");
		tmp = ft_strcat(tmp, env->content);
		tmp = ft_strcat(tmp, "\"");
		tab[i] = ft_strdup(tmp);
		free(tmp);
		env = env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int					ft_size(t_env_variable *lst)
{
	int				i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_env_variable		*order(t_env_variable *list)
{
	char			*content;
	t_env_variable	*tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (ft_strcmp(tmp->content, tmp->next->content) > 0)
		{
			content = tmp->content;
			tmp->content = tmp->next->content;
			tmp->next->content = content;
			tmp = list;
		}
		else
			tmp = tmp->next;
	}
	tmp = list;
	return (tmp);
}
