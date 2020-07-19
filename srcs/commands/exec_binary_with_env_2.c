/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_with_env_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:33:13 by abourin           #+#    #+#             */
/*   Updated: 2020/03/11 07:08:42 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_binary_norm(char ***t)
{
	if (!((*t) = malloc(sizeof(char *) * 2)))
		return (1);
	(*t)[0] = ft_strdup("TERM=xterm");
	(*t)[1] = NULL;
	return (0);
}
