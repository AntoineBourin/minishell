/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:55:26 by nveron            #+#    #+#             */
/*   Updated: 2019/10/17 16:21:22 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	conv;
	unsigned char	*cpy;

	i = 0;
	cpy = s;
	conv = c;
	while (i < n)
	{
		cpy[i] = conv;
		i++;
	}
	return (s);
}
