/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:40:05 by nveron            #+#    #+#             */
/*   Updated: 2019/10/17 13:23:34 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int last_index;

	i = 0;
	last_index = -1;
	while (s[i])
	{
		if (c == s[i])
			last_index = i;
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	if (last_index == -1)
		return (NULL);
	else
		return ((char *)(s + last_index));
}
