/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:10:44 by abourin           #+#    #+#             */
/*   Updated: 2020/02/29 16:15:37 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_sort_norm1(t_comp *c1, char *str, int *tmp)
{
	while (str[c1->i] == ' ')
		(c1->i)++;
	(*tmp) = c1->i;
	if (str[c1->i] == 34)
		c1->exp_1 *= -1;
	if (str[c1->i] == 39)
		c1->exp_2 *= -1;
}

void			ft_sort_norm2(t_comp *c1, char **str, char **cop)
{
	if ((*str)[c1->i + 1] == 34 || (*str)[c1->i + 1] == 39)
	{
		if ((*str)[c1->i + 1] == 34)
			c1->exp_1 *= -1;
		if ((*str)[c1->i + 1] == 39)
			c1->exp_2 *= -1;
		(*cop)[c1->j + 1] = ' ';
		(*str)[c1->i + 1] = ' ';
	}
	(*cop)[c1->j] = (*str)[c1->i];
	(c1->i)++;
	(c1->j)++;
}

int				ft_while(int i, int c, char const *s)
{
	while (s[i] == c)
		i++;
	return (i);
}

char			**ft_crash(char **str, int j)
{
	while (j > 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
	return (NULL);
}
