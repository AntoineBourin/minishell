/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:47:40 by nveron            #+#    #+#             */
/*   Updated: 2019/10/17 18:03:19 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;
	const char		*str;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	str = ft_strlen(s1) > ft_strlen(s2) ? s1 : s2;
	while (str[i] && i < n)
	{
		a = (unsigned char)s1[i];
		b = (unsigned char)s2[i];
		if (a > b || a < b)
			return (a - b);
		i++;
	}
	return (0);
}
