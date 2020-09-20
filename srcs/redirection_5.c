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

char		**cut_cmd_for_pipe_and_redirection_2(char **str)
{
	int		i;
	char	**ac;

	ac = NULL;
	if (cut_cmd_for_pipe_and_redirection_malloc_2(&ac, *str))
		return (NULL);
	i = cut_cmd_for_pipe_and_redirection_norme1_2(*str, ac, 1, 0);
	(*str) += i;
	i = cut_cmd_for_pipe_and_redirection_norme1_2(*str, ac, 0, 1);
	(*str) += i;
	i = cut_cmd_for_pipe_and_redirection_norme1_2(*str, ac, 1, 2);
	while (**str == ' ')
		(*str)++;
	return (ac);
}
