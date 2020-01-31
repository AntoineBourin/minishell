/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:26:11 by nveron            #+#    #+#             */
/*   Updated: 2019/10/17 16:29:20 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*cpysrc;
	char		comp;

	comp = c;
	cpysrc = s;
	i = 0;
	while (i < n)
	{
		if (cpysrc[i] == comp)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
