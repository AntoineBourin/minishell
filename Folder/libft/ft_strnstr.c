/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:33:36 by nveron            #+#    #+#             */
/*   Updated: 2019/10/17 17:50:13 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;
	size_t len2;

	i = 0;
	len2 = ft_strlen(little);
	if (!little[0])
		return ((char *)big);
	if (!big[0])
		return (NULL);
	while (*big && i < len)
	{
		j = 0;
		while (big[j] == little[j] && little[j] && (j + i) < len)
			j++;
		if (j == len2)
			return ((char *)big);
		else
			big++;
		i++;
	}
	return (0);
}
