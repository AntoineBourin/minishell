/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_error_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:21:56 by cnotin            #+#    #+#             */
/*   Updated: 2020/10/02 15:53:28 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	helping(char *s, int i)
{
	if (s[i] == '|')
	{
		ft_putstr_fd("minishell : ", 1);
		ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
	}
	else
	{
		ft_putstr_fd("minishell : ", 1);
		ft_putstr_fd("syntax error near unexpected token `;'\n", 1);
	}
}

int			help_search(char *s, int i)
{
	if (s[i + 1] == ';')
		return (2);
	return (1);
}

int			help_redir(int redir, int back)
{
	if (is_redir(redir, back) == 1)
		return (1);
	else if (is_redir(redir, back) == 2)
		return (2);
	else
		return (0);
}

int			again_2(char *s)
{
	int	i;

	i = ft_strlen(s);
	while (i-- > 0)
	{
		if (s[i] == ';' || s[i] == '|')
		{
			i--;
			if (s[i] == ' ' || s[i] == '\t')
			{
				while (s[i] == ' ' || s[i] == '\t')
					i--;
				if (s[i] == '>' || s[i] == '<' || s[i] == '|')
				{
					helping(s, i);
					return (0);
				}
			}
		}
	}
	return (1);
}

int			again_3(char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	if (s[0] == '|' || s[i] == '|')
	{
		ft_putstr_fd("minishell : ", 1);
		ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
		return (0);
	}
	else if (s[0] == '>')
	{
		ft_putstr_fd("minishell : ", 1);
		ft_putstr_fd("syntax error near unexpected token `>'\n", 1);
		return (0);
	}
	else if (s[0] == '<')
	{
		ft_putstr_fd("minishell : ", 1);
		ft_putstr_fd("syntax error near unexpected token `<'\n", 1);
		return (0);
	}
	return (1);
}
