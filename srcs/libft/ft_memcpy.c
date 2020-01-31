/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:10:24 by nveron            #+#    #+#             */
/*   Updated: 2019/10/22 15:50:38 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*cpydest;
	const char	*cpysrc;

	if (dest == NULL && src == NULL)
		return (NULL);
	cpysrc = src;
	cpydest = dest;
	i = 0;
	while (i < n && dest && src)
	{
		cpydest[i] = cpysrc[i];
		i++;
	}
	return (dest);
}
