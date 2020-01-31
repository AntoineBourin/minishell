/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:12:10 by nveron            #+#    #+#             */
/*   Updated: 2019/10/22 15:27:05 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*result;
	int				size;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	i = 0;
	if ((unsigned int)size <= start)
	{
		if (!(result = malloc(1 * sizeof(char))))
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	if (!(result = malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (i < len && s[i + start])
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}
