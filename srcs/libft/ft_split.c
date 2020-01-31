/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:27:50 by nveron            #+#    #+#             */
/*   Updated: 2019/11/14 14:26:14 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_compt(char const *s, char c)
{
	size_t	compt;
	int		start;
	int		end;

	start = 0;
	end = 0;
	compt = 0;
	while (s[end])
	{
		if (s[end] == c)
		{
			if (start - end < 0)
				compt++;
			end++;
			start = end;
		}
		else
			end++;
	}
	if (start - end < 0)
		compt++;
	return (compt);
}

static size_t	ft_size(size_t i, char const *s, char c)
{
	size_t size;

	size = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
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

char			**ft_split(char const *s, char c)
{
	char	**new;
	size_t	i;
	size_t	j;
	size_t	k;

	new = NULL;
	j = 0;
	i = 0;
	if (s != NULL)
	{
		if (!(new = malloc((ft_compt(s, c) + 1) * sizeof(char*))))
			return (NULL);
		while (s[i])
		{
			k = 0;
			i = ft_while(i, c, s);
			if (!(new[j] = malloc(sizeof(char) * ft_size(i, s, c) + 1)))
				return (ft_crash(new, j));
			while (s[i] != c && s[i])
				new[j][k++] = s[i++];
			new[j++][k] = '\0';
		}
		new[ft_compt(s, c)] = NULL;
	}
	return (new);
}
