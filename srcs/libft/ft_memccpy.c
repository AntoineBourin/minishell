/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:30:19 by nveron            #+#    #+#             */
/*   Updated: 2019/10/19 12:03:37 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		d;
	unsigned char		*cpydest;
	const unsigned char	*cpysrc;

	d = c;
	cpysrc = src;
	cpydest = dest;
	i = 0;
	while (i < n)
	{
		cpydest[i] = cpysrc[i];
		if (cpysrc[i] == d)
		{
			i++;
			return (dest + i);
		}
		i++;
	}
	return (NULL);
}
