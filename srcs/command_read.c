/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:06:25 by abourin           #+#    #+#             */
/*   Updated: 2020/01/31 14:19:05 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*command_read(t_env *env)
{
	char	buff[4096];
	char	*result;
	int		bytes_readen;

	(void)env;
	if (!(result = malloc(sizeof(char) * 1)))
		return NULL;
	result[0] = '\0';
	while ((bytes_readen = read(0, buff, 4095)) > 0)
	{
		printf("BUFFER RESULT %s\n", buff);
	}
	return (result);
}
