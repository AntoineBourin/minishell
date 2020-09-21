/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/13 16:01:31 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_if_quote_norm(int j, int i, t_env *env, int x)
{
	if (x == 34)
	{
		env->presence_of_34 *= -1;
	}
	if (x == 39)
	{
		env->presence_of_39 *= -1;
	}
	if (i == j)
		return (2);
	return (0);
}

int		check_if_quote(char *str, int j, t_env *env)
{
	int i;
	int x;

	env->presence_of_34 = -1;
	env->presence_of_39 = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 && env->presence_of_39 < 0)
			if (check_if_quote_norm(j, i, env, 34))
				return (2);
		if (str[i] == 39 && env->presence_of_34 < 0)
			if (check_if_quote_norm(j, i, env, 39))
				return (2);
		x = check_if_quote_norm3(str, &i, j, env);
		if (x)
			return (x);
		i++;
	}
	return (0);
}

int		check_if_is_the_end_of_the_cmd(char *str, int i)
{
	if (str[i] && str[i] != ' ')
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	echo_main_norm(char *str, int i, t_env *env)
{
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (check_if_quote(str, i, env) == 1)
		{
			ft_putchar_fd(str[i], 1);
		}
		else if (check_if_quote(str, i, env) == 0
				&& check_if_is_the_end_of_the_cmd(str, i) == 0)
			ft_putchar_fd(str[i], 1);
		i++;
	}
}

void	echo_main(char *str, char **ac, t_env *env)
{
	int i;
	int j;

	i = 0;
	j = 1;
	if (ac[j] != '\0' && ft_strncmp(ac[j], "-n", 3) == 0)
	{
		while (ac[j] != '\0' && ft_strncmp(ac[j], "-n", 3) == 0)
		{
			while (str[i] != '-')
				i++;
			i += 2;
			j++;
		}
	}
	else
		i = echo_main_norm_4(str, i);
	echo_main_norm(str, i, env);
	if (ft_strncmp(ac[1], "-n", 3) != 0)
		ft_putchar_fd('\n', 1);
	env->last_program_return = 0;
}
