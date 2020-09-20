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

int			cut_cmd_norm1_2(char *str, char **ac, int x)
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
	while (str[i] && ((check_if_char_in_str_is_in_str2_modif("|", cpy) &&
check_if_char_is_in_str_modif(cpy, "|", i) != 1) || (
check_if_char_in_str_is_in_str2_modif("|", cpy) <= 0 &&
check_if_char_is_in_str_modif(cpy, "<>|", i) != 1)))
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

int			cut_cmd_norm2(char *str, char **ac, int x)
{
	int		i;
	int		e;
	char	*cpy;

	i = 0;
	e = 1;
	cpy = NULL;
	cpy = str;
	while (str[i] && check_if_char_is_in_str_modif(cpy, "<>|", i) == 1)
	{
		ac[x][i] = (str)[i];
		i++;
	}
	ac[x][i] = '\0';
	return (i);
}

int			cut_cmd_norm2_2(char *str, char **ac, int x)
{
	int		i;
	int		e;
	char	*cpy;

	i = 0;
	e = 1;
	cpy = NULL;
	cpy = str;
	while (str[i] && check_if_char_is_in_str_modif(cpy, "|", i) == 1)
	{
		ac[x][i] = (str)[i];
		i++;
	}
	ac[x][i] = '\0';
	return (i);
}

int			cut_cmd_for_pipe_and_redirection_norme1(char *str,
			char **ac, int j, int x)
{
	int		i;
	int		e;
	char	*cpy;

	i = 0;
	e = 1;
	cpy = NULL;
	if (j)
	{
		return (cut_cmd_norm1(str, ac, x));
	}
	else
	{
		return (cut_cmd_norm2(str, ac, x));
	}
	return (i);
}

int			cut_cmd_for_pipe_and_redirection_norme1_2(char *str,
			char **ac, int j, int x)
{
	int		i;
	int		e;
	char	*cpy;

	i = 0;
	e = 1;
	cpy = NULL;
	if (j)
	{
		return (cut_cmd_norm1_2(str, ac, x));
	}
	else
	{
		return (cut_cmd_norm2_2(str, ac, x));
	}
	return (i);
}
