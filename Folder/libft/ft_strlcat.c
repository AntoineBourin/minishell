/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:56:00 by nveron            #+#    #+#             */
/*   Updated: 2019/10/23 16:47:06 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	lendest;
	size_t	lensrc;

	lendest = ft_strlen(dest);
	lensrc = ft_strlen(src);
	i = 0;
	j = 0;
	if (size >= lendest)
	{
		while (dest[i] && i < size)
		{
			i++;
		}
		while (src[j] && i < (size - 1))
		{
			dest[i] = src[j];
			j++;
			i++;
		}
		dest[i] = '\0';
		return (lendest + lensrc);
	}
	return (lensrc + size);
}
