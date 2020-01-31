/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:36:54 by nveron            #+#    #+#             */
/*   Updated: 2019/11/13 10:52:41 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*cpy;

	if (!(cpy = malloc(nmemb * size)))
		return (NULL);
	ft_bzero(cpy, size * nmemb);
	return (cpy);
}
