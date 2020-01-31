/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:34:04 by nveron            #+#    #+#             */
/*   Updated: 2019/10/18 11:13:00 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_exeption(int sign, const char *nptr)
{
	if (ft_strncmp("-2147483649", nptr, ft_strlen(nptr)) == 0)
		return (2147483647);
	else if (sign == 1)
		return (-1);
	else
		return (0);
}

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
			|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

int			ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		result;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (((result * 10) <= 2147483640 && ((sign == -1) && (result + nptr[i] -
	'0') <= 214748372)) || ((sign == 1) && result + nptr[i] - '0' <= 214748381))
			result = (result * 10) + (nptr[i] - '0');
		else
			return (ft_exeption(sign, nptr));
		i++;
	}
	return (result * sign);
}
