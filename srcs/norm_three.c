/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:34:43 by abourin           #+#    #+#             */
/*   Updated: 2020/02/29 16:55:41 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_norm1(char ***res, t_comp *c1, int begin_index, char **tmp)
{
	c1->i = 0;
	c1->j = 0;
	while ((**res)[c1->i] && (int)c1->i < begin_index - 1)
	{
		(*tmp)[c1->i] = (**res)[c1->i];
		(c1->i)++;
	}
	c1->k = c1->i;
}

void	move_init(t_env *env)
{
	int				check_error;
	char			*buff;
	t_env_variable	*home;

	home = get_env_variable_if_exist(env->env_variables, "HOME");
	if (home && home->content)
		check_error = chdir(home->content);
	else
		check_error = chdir("/Users");
	buff = NULL;
	buff = getcwd(buff, 1000000);
	if (!(env->curr_path = malloc(sizeof(char) * ft_strlen(buff))))
		return ;
	env->curr_path = buff;
}
