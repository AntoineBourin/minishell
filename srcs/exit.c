/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/10/02 15:52:55 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_exit_and_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			exit(255);
		i++;
	}
	exit(ft_atoi(str));
}

void		ft_exit(t_env *env)
{
	if (env->ac[1] != '\0' && env->ac[2] != '\0')
	{
		ft_putstr_fd("./Minishell: exit: too many arguments\n", 1);
		env->last_program_return = 1;
	}
	if (env->ac[1] != '\0')
		ft_exit_and_check(env->ac[1]);
	else
		exit(env->last_program_return);
}

int			again(char *s)
{
	int		i;

	if (!again_2(s))
		return (0);
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == ';' && s[i - 2] == ';')
		{
			ft_putstr_fd("minishell : ", 1);
			ft_putstr_fd("syntax error near unexpected token `;;'\n", 1);
			return (0);
		}
		if (s[i] == ';' && (s[i - 1] == '>' || s[i - 1] == '<') &&
			s[i - 2] != '\\')
		{
			ft_putstr_fd("minishell : ", 1);
			ft_putstr_fd("syntax error near unexpected token `;'\n", 1);
			return (0);
		}
		i--;
	}
	return (1);
}

void		error_2(char *s, int i)
{
	if (s[i] == '|' || s[i] == '\0' || s[i] == ';')
	{
		ft_putstr_fd("minishell : ", 1);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 1);
	}
	else if (s[i] == '>' && s[i + 1] == '>')
	{
		ft_putstr_fd("minishell : ", 1);
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 1);
	}
	else if (s[i] == '>')
	{
		ft_putstr_fd("minishell : ", 1);
		ft_putstr_fd("syntax error near unexpected token `>'\n", 1);
	}
	else if (s[i] == '<')
	{
		ft_putstr_fd("minishell : ", 1);
		ft_putstr_fd("syntax error near unexpected token `<'\n", 1);
	}
}

int			ft_error(char *s, t_env *env)
{
	char	**tmp;

	if (!help_error(s, env))
		return (0);
	tmp = split_modif(s);
	while (*tmp)
	{
		if (!check_redir(*tmp))
			*tmp = escape_backslash(*tmp, env);
		else if (!error_redir(*tmp, env))
		{
			ft_putstr_fd("minishell : ", 1);
			ft_putstr_fd("syntax error near unexpected token `;'\n", 1);
			ft_free_tab(tmp);
			env->last_program_return = 1;
			return (0);
		}
		tmp++;
	}
	ft_free_tab(tmp);
	return (1);
}
