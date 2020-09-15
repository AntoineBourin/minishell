/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:35:56 by abourin           #+#    #+#             */
/*   Updated: 2020/02/29 11:49:48 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_norm1(char ***res, t_comp *c1, int begin_index, char **tmp)
{
	c1->i = 0;
	c1->j = 0;
	while (*tmp && (*tmp)[c1->i] && (**res)[c1->i] &&
	(int)c1->i < begin_index - 1)
	{
		(*tmp)[c1->i] = (**res)[c1->i];
		(c1->i)++;
	}
	c1->k = c1->i;
}

void	replace_env_norm2(int *length, t_env_variable *env)
{
	if (env == NULL)
		(*length) = 0;
	else
		(*length) = ft_strlen(env->content) - ft_strlen(env->name);
}

void	replace_env_name_by_value(char **res, t_env_variable *env,
		int begin_index, int end_index)
{
	int		length;
	char	*tmp;
	char	*content;
	t_comp	c1;

	replace_env_norm2(&length, env);
	if (!(tmp = malloc(sizeof(char) * (ft_strlen(*res) + length + 1))))
		return ;
	tmp[ft_strlen(*res) + length] = '\0';
	content = env != NULL ? env->content : NULL;
	replace_env_norm1(&res, &c1, begin_index, &tmp);
	while (content && content[c1.j] && tmp && tmp[c1.i])
	{
		tmp[c1.i] = content[c1.j];
		(c1.i)++;
		(c1.j)++;
	}
	while (tmp && tmp[c1.i] && (*res)[c1.k + end_index - begin_index + 1])
	{
		tmp[c1.i] = (*res)[c1.k + end_index - begin_index + 1];
		(c1.i)++;
		(c1.k)++;
	}
	tmp[c1.i] = '\0';
	*res = tmp;
}
