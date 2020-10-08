/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:58:05 by cnotin            #+#    #+#             */
/*   Updated: 2020/10/02 02:49:40 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			len_back(char *str)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || (str[i] == '\\' && str[i + 1] == '\\'))
			i++;
		i++;
		len++;
	}
	return (len);
}

char		*escape_backslash(char *str, t_env *env)
{
	int		i;
	int		j;
	char	*ret;

	(void)env;
	i = 0;
	if (!(ret = (char *)malloc(sizeof(char) * len_back(str) + 1)))
		return (NULL);
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\\') || (str[i] == '\\' && str[i + 1] == '\\'))
			i++;
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

int			is_redir(int redir, int back)
{
	if (redir == 1 && (back % 2 != 0))
		return (0);
	else if ((redir == 1 && (back % 2 == 0)) ||
		(redir == 2 && (back % 2 != 0)))
		return (1);
	else
		return (2);
}

int			check_redir(char *s)
{
	int		i;
	int		redir;
	int		back;

	i = ft_strlen(s);
	while (i-- > 0)
	{
		back = 0;
		redir = 0;
		if (s[i] == '>')
		{
			redir++;
			while (s[--i] == '>')
				redir++;
			if (s[i] == '\\')
				while (s[i--] == '\\')
					back++;
			help_redir(redir, back);
		}
	}
	return (0);
}

int			search_pipe(char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s);
	while (i < j)
	{
		while (s[i] == '<' || s[i] == '>' || s[i] == ';')
			i++;
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] == c)
		{
			if (s[i + 1] == c || s[i + 1] == ';' || s[i + 1] == '>' ||
				s[i + 1] == '<')
			{
				ft_putstr_fd("minishell : ", 1);
				ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
				return (2);
			}
		}
		i++;
	}
	return (0);
}
