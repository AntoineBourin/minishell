/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:06:25 by nveron            #+#    #+#             */
/*   Updated: 2020/02/29 12:28:37 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_check_red(char *str, char *sep)
{
	t_comp all;

	all.exp_1 = -1;
	all.exp_2 = -1;
	all.exp_3 = -1;
	all.i = 0;
	while (str[all.i])
	{
		if (ft_norm_check_red(&all, str) == 0)
			return (0);
		all.j = 0;
		while (sep[all.j])
		{
			if (str[all.i] == sep[all.j] &&
			all.exp_1 < 0 && all.exp_2 < 0 && all.exp_3 < 0)
				return (1);
			all.j++;
		}
		all.i++;
		if (all.exp_3 > 0)
			all.exp_3 *= -1;
	}
	return (0);
}

int				ft_check_red_char(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_red_norm5(char **copy, t_comp *c1, char *str)
{
	(*copy)[c1->j] = str[c1->i];
	(c1->j)++;
}

void	ft_red_norm6(t_comp *c1, t_list *commands, t_env *env, char *str)
{
	c1->i += execute_pipes_command(commands, env, c1->cop, str);
	c1->i -= (ft_strlen(c1->cop) + 1);
}

void	ft_red_norm7(char *str, t_comp *c1, t_list *commands, t_env *env)
{
	if (ft_check_red_char(str[c1->i], "<") == 1)
		ft_red_norm3(c1, commands, env, str);
	else if (ft_check_red_char(str[c1->i], ">") == 1 &&
	ft_check_red_char(str[c1->i + 1], ">") != 1)
		ft_red_norm1(str, c1, commands, env);
	else if (ft_check_red_char(str[c1->i], ">") == 1 &&
	ft_check_red_char(str[c1->i + 1], ">") == 1)
		ft_red_norm2(str, c1, commands, env);
	else if (ft_check_red_char(str[c1->i], "|") == 1)
		ft_red_norm6(c1, commands, env, str);
}

void	ft_red(t_list *commands, t_env *env, char *str)
{
	char	*copy;
	t_comp	c1;

	if (ft_red_norm4(&c1, str, &copy, env) > 0)
		return ;
	env->last_program_return = 0;
	while (str[c1.i])
	{
		if (ft_check_red_char(str[c1.i], "<>|") != 1)
			ft_red_norm5(&copy, &c1, str);
		else
		{
			while (c1.j > 1 && copy[c1.j] && copy[c1.j - 1]
			&& copy[c1.j - 1] == ' ')
				(c1.j)--;
			copy[c1.j] = '\0';
			c1.cop = copy;
			ft_red_norm7(str, &c1, commands, env);
			c1.j = 0;
		}
		(c1.i)++;
	}
	free(copy);
}
