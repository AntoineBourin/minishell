/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:21:08 by abourin           #+#    #+#             */
/*   Updated: 2020/02/06 11:20:00 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg_quotes(char *arg, char charset)
{
	int		is_quoted;
	int		i;

	i = 0;
	if (arg[0] && arg[0] == '"')
	{
		is_quoted = 1;
		i++;
	}
	else
		is_quoted = 0;
	while (arg[i])
	{
		if (arg[i] == charset)
		{
			arg[i] = '\0';
			return (arg);
		}
		if (arg[i] == ' ' && !is_quoted)
		{
			arg[i] = '\0';
			return (arg);
		}
		if (arg[i] == '"' && is_quoted)
		{
			arg[i] = '\0';
			return (arg + 1);
		}
		i++;
	}
	return (arg);
}
