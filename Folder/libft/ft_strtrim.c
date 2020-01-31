/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:40:13 by nveron            #+#    #+#             */
/*   Updated: 2019/10/18 10:16:12 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_ischarset(char s1, const char *set)
{
	size_t i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(const char *s1, const char *set)
{
	int		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && ft_ischarset(*s1, set))
		s1++;
	end = ft_strlen(s1) - 1;
	while (end > 0 && ft_ischarset(s1[end], set))
		end--;
	if (end == 0 && *s1 == '\0')
		return (ft_calloc(1, sizeof(char)));
	return (ft_substr(s1, 0, end + 1));
}
