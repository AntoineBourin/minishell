/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_read_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/10/01 12:46:05 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_if_char_in_str_is_in_str2_modif(char *charset, char *str)
{
	int i;
	int j;
	int x;
	int presence_of_34;
	int presence_of_39;

	presence_of_34 = -1;
	presence_of_39 = -1;
	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == 34 && presence_of_39 < 0)
			presence_of_34 *= -1;
		if (str[i] == 39 && presence_of_34 < 0)
			presence_of_39 *= -1;
		if (presence_of_39 < 0 && presence_of_34 < 0)
		{
			x = check_norm_1(str, &i, &j, charset);
			if (x)
				return (x);
		}
		i++;
	}
	return (0);
}

void		check_if_norm1(char
*str, int i, int *presence_of_39, int *presence_of_34)
{
	if (str[i] == 34 && *presence_of_39 < 0)
		(*presence_of_34) *= -1;
	if (str[i] == 39 && *presence_of_34 < 0)
		(*presence_of_39) *= -1;
}

void		check_if_char_is_in_str_modif_norm2(int *x, int *y, int *i)
{
	*x = -1;
	*y = -1;
	*i = 0;
}

int			check_if_char_is_in_str_modif(char *str, char *charset, int x)
{
	int i;
	int j;
	int presence_of_34;
	int presence_of_39;

	check_if_char_is_in_str_modif_norm2(&presence_of_34, &presence_of_39, &i);
	while (str[i])
	{
		j = 0;
		check_if_norm1(str, i, &presence_of_39, &presence_of_34);
		if (presence_of_39 < 0 && presence_of_34 < 0)
		{
			if (str[i] == 92 && str[i + 1] != '\0')
				i++;
			else
				while (charset[j])
				{
					if (charset[j] == str[i] && i == x)
						return (1);
					j++;
				}
		}
		i++;
	}
	return (0);
}

void		execute_and_sort_cmd(char *str, t_env *env)
{
	if (check_if_char_in_str_is_in_str2_modif("<>|", str))
		redirection_sort(str, env);
	else
		command_read(str, env);
}
