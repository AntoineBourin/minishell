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
		c.end = s[c.end - 1] == 92 && c.end > 0 && s[c.end] ? c.end + 1 : c.end;
	}
	if (c.start - c.end < 0)
		(c.compt)++;
	return (c.compt);
}

static size_t	ft_size(size_t i, char const *s, char c)
{
	t_comp	all;

	all.size = 0;
	all.exp_1 = -1;
	all.exp_2 = -1;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == 92)
		{
			if (ft_norm_size(&i, s, &(all.size)) == 1)
				break ;
		}
		else
		{
			all.exp_1 = s[i] == 39 ? all.exp_1 *= -1 : all.exp_1;
			all.exp_2 = s[i] == 34 ? all.exp_2 *= -1 : all.exp_2;
			if (s[i] == c && all.exp_1 < 0 && all.exp_2 < 0)
				break ;
			all.size++;
			i++;
		}
	}
	return (all.size);
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
			if (!(new[c1.j] = malloc(sizeof(char) * ft_size(c1.i, s, c) + 2)))
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
