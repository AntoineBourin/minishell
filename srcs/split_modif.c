/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_modif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:27:50 by nveron            #+#    #+#             */
/*   Updated: 2020/02/29 11:12:00 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static size_t	ft_compt(char const *s, char ch)
{
	t_comp c;

	c.start = 0;
	c.end = 0;
	c.compt = 0;
	c.exp_1 = -1;
	c.exp_2 = -1;
	while (s[c.end])
	{
		c.exp_1 = s[c.end] == 39 ? c.exp_1 * -1 : c.exp_1;
		c.exp_2 = s[c.end] == 34 ? c.exp_2 * -1 : c.exp_2;
		if (s[c.end] == ch && c.exp_1 < 0 && c.exp_2 < 0)
		{
			if (c.start - c.end < 0)
				(c.compt)++;
			(c.end)++;
			c.start = c.end;
		}
		else
			(c.end)++;
	}
	if (c.start - c.end < 0)
		(c.compt)++;
	return (c.compt);
}

static size_t	ft_size(size_t i, char const *s, char c)
{
	size_t	size;
	int		exp_1;
	int		exp_2;

	size = 0;
	exp_1 = -1;
	exp_2 = -1;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == 39)
			exp_1 *= -1;
		if (s[i] == 34)
			exp_2 *= -1;
		if (s[i] == c && exp_1 < 0 && exp_2 < 0)
			break ;
		size++;
		i++;
	}
	return (size);
}

static int		ft_while(int i, int c, char const *s)
{
	while (s[i] == c)
		i++;
	return (i);
}

static char		**ft_crash(char **str, int j)
{
	while (j > 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
	return (NULL);
}

int				ft_split_modif_norm1(t_comp *c1, const char *s, int i, char c)
{
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

char			**ft_split_modif(char const *s, char c)
{
	char	**new;
	t_comp	c1;

	ft_split_modif_norm2(&c1, &new, &(c1.j), &(c1.i));
	if (s != NULL)
	{
		if (!(new = malloc((ft_compt(s, c) + 1) * sizeof(char*))))
			return (NULL);
		while (s[c1.i])
		{
			c1.k = 0;
			c1.i = ft_while(c1.i, c, s);
			if (!(new[c1.j] = malloc(sizeof(char) * ft_size(c1.i, s, c) + 1)))
				return (ft_crash(new, c1.j));
			while (s[c1.i])
			{
				if (ft_split_modif_norm1(&c1, s, c1.i, c) > 0)
					break ;
				new[c1.j][(c1.k)++] = s[(c1.i)++];
			}
			new[(c1.j)++][(c1.k)] = '\0';
		}
		new[ft_compt(s, c)] = NULL;
	}
	return (new);
}
