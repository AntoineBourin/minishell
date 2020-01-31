/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:01:27 by nveron            #+#    #+#             */
/*   Updated: 2019/11/14 10:54:29 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stridup(const char *s, int start)
{
	char	*copy;
	int		i;

	i = 0;
	while (s[start + i])
		i++;
	if (!(copy = malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (s[start + i])
	{
		copy[i] = s[start + i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
