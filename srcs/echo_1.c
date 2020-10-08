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

int		check_if_quote_norm2(char *str, int *i, int j)
{
	if (str[*i] == 92 && str[(*i) + 1] != '\0')
	{
		if ((*i) == j)
			return (2);
		(*i)++;
	}
	else if (str[*i] == 92 && str[(*i) + 1] == '\0')
	{
		if ((*i) == j)
			return (2);
	}
	return (0);
}

int		check_if_quote_norm3(char *str, int *i, int j, t_env *env)
{
	if (env->presence_of_39 < 0)
	{
		if (check_if_quote_norm2(str, i, j))
			return (2);
	}
	else if (env->presence_of_34 < 0)
	{
		return (0);
	}
	else
	{
		if ((*i) == j)
			return (1);
	}
	return (0);
}

int		echo_main_norm_4(char *str, int i)
{
	while (ft_strncmp(str + i, "echo", 4) != 0)
		i++;
	i += 4;
	while (str[i] == 39 || str[i] == 34)
		i++;
	while (str[i] == ' ')
		i++;
	return (i);
}
