/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_modif_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:27:50 by nveron            #+#    #+#             */
/*   Updated: 2020/03/04 07:48:16 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int				ft_split_modif_norm1(t_comp *c1, const char *s, int i, char c)
{
	if (i > 0 && s[i - 1] == 92)
		return (0);
	if (s[i] == 39)
		c1->exp_1 *= -1;
	if (s[i] == 34)
		c1->exp_2 *= -1;
	if (s[i] == c && c1->exp_1 < 0 && c1->exp_2 < 0)
		return (1);
	return (0);
}

void			ft_split_modif_norm2(t_comp *c1,
		char ***new, size_t *j, size_t *i)
{
	c1->exp_1 = -1;
	c1->exp_2 = -1;
	(*new) = NULL;
	(*j) = 0;
	(*i) = 0;
}

int				ft_norm_size(size_t *i, char const *s, size_t *size)
{
	(*i)++;
	if (s[*i])
		(*i)++;
	(*size) += 2;
	if (!(s[(*i)]))
		return (1);
	return (0);
}
