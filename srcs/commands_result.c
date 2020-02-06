/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_result.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 11:55:22 by abourin           #+#    #+#             */
/*   Updated: 2020/02/05 12:04:26 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_commands_result(t_list *commands)
{
	// Redirections will be applied to commands here
	while (commands)
	{
		if (commands->result)
		{
			if (ft_strncmp(commands->result, "exit", 4) == 0)
				exit(0);
			ft_putstr_fd(commands->result, 1);
			if (commands->separator == 0)
				ft_putchar_fd('\n', 1);
		}
		commands = commands->next;
	}
}
