/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:38:45 by cnotin            #+#    #+#             */
/*   Updated: 2020/10/02 19:30:36 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_search(char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s);
	while (i++ < j)
	{
		if (s[i] == c)
		{
			i++;
			if (s[i] == ';' && s[i - 2] != '\\')
				return (2);
			if (s[i] == ' ' || s[i] == '\t')
			{
				while (s[i] == ' ' || s[i] == '\t')
					i++;
				if (s[i] == ';')
				{
					help_search(s, i);
				}
			}
		}
	}
	return (0);
}

int			ft_error_semi(char *s, t_env *env)
{
	int		i;

	if (s[0] == ';')
	{
		ft_putstr_fd("minishell : syntax error near unexpected token `;'\n", 1);
		env->last_program_return = 1;
		return (0);
	}
	if (ft_search(s, ';') == 2)
	{
		ft_putstr_fd("minishell : ", 1);
		ft_putstr_fd("syntax error near unexpected token `;;'\n", 1);
		env->last_program_return = 1;
		return (0);
	}
	i = -1;
	while (s[++i])
	{
		if (s[i] == ';' && s[i + 1] == '|')
		{
			error_semi_norm(env);
			return (0);
		}
	}
	return (1);
}

int			call_error(int redir, int back, t_env *env)
{
	if ((redir >= 5) || (redir == 4 && (back % 2) == 0))
	{
		ft_putstr_fd("minishell : ", 1);
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 1);
		env->last_program_return = 1;
		return (0);
	}
	else if (((redir == 3 && (back % 2 == 0)) ||
				(redir == 4 && (back % 2 != 0))))
	{
		ft_putstr_fd("minishell : syntax error near unexpected token `>'\n", 1);
		env->last_program_return = 1;
		return (0);
	}
	return (1);
}

int			error_redir_2(char *s, t_env *env)
{
	int		i;

	i = 0;
	(void)env;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
		{
			while (s[i] == '>' || s[i] == '<')
				i++;
			while (s[i] == ' ' || s[i] == '\t')
				i++;
			if (s[i] == '>' || s[i] == '<' || s[i] == '|' || s[i] == '\0')
			{
				error_2(s, i);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int			error_redir(char *s, t_env *env)
{
	int		i;
	int		redir;
	int		back;

	i = ft_strlen(s);
	while (i > 0)
	{
		back = 0;
		redir = 0;
		if (s[i] == '>' || s[i] == '<')
		{
			redir++;
			while (s[--i] == '>' || s[i] == '<')
				redir++;
			if (s[i] == '\\')
				while (s[i--] == '\\')
					back++;
			if (!call_error(redir, back, env) || !error_redir_2(s, env))
				return (0);
		}
		i--;
	}
	return (1);
}
