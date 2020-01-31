/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:27:50 by nveron            #+#    #+#             */
/*   Updated: 2019/11/14 11:57:32 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_split_space(char *str, char c)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	copy = ft_strdup(str);
	while (str[i])
	{
		if (str[i] != c)
		{
			copy[j] = str[i];
			j++;
		}
		i++;
	}
	copy[j] = '\0';
	return (copy);
}
