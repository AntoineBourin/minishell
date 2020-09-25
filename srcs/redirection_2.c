/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/10 16:42:10 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int			cut_cmd_norm1(char *str, char **ac, int x)
{
	int		i;
	int		e;
	char	*cpy;

	i = 0;
	e = 1;
	cpy = NULL;
	while (*str == ' ')
		str++;
	cpy = str;
	while (str[i] && check_if_char_is_in_str_modif(cpy, "<>|", i) != 1)
	{
		ac[x][i] = (str)[i];
		i++;
	}
	ac[x][i] = '\0';
	while (i - e >= 0 && ac[x][i - e] == ' ')
	{
		ac[x][i - e] = '\0';
		e++;
	}
	return (i);
}

void		exec_cmd_redirection(t_cmdlist **list, t_env *env)
{
	t_cmdlist *list_2;

	list_2 = *list;
	while (list_2->fd_out->next)
	{
		list_2->fd_out = list_2->fd_out->next;
	}
	while ((*list)->fd_in->next)
	{
		(*list)->fd_in = (*list)->fd_in->next;
	}
	redirection(list_2->command, (*list)->fd_in->fd, list_2->fd_out->fd, env);
}