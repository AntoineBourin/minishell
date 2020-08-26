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
