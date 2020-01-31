/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:07:07 by nveron            #+#    #+#             */
/*   Updated: 2019/10/20 11:08:19 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned const char	*cpysrc;
	unsigned char		*cpydest;
	unsigned char		temp[n];

	cpysrc = src;
	cpydest = dest;
	i = 0;
	if (dest == NULL || src == NULL)
		return (NULL);
	while (i < n)
	{
		temp[i] = cpysrc[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		cpydest[i] = temp[i];
		i++;
	}
	return ((void *)cpydest);
}
