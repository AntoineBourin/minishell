/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:06:25 by nveron            #+#    #+#             */
/*   Updated: 2020/03/04 07:47:55 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_norm_check_red(t_comp *all, char *str)
{
	if (str[all->i] == 92)
	{
		(all->exp_3) *= -1;
		if (str[all->i + 1] == '\0')
			return (0);
		(all->i)++;
	}
	if (str[all->i] == 39 && (all->exp_3) < 0)
		(all->exp_1) *= -1;
	if (str[all->i] == 34 && (all->exp_3) < 0)
		(all->exp_2) *= -1;
	return (1);
}

void	ft_red_norm1(char *str, t_comp *c1, t_list *commands, t_env *env)
{
	int fd;
	int oldfd;

	oldfd = dup(1);
	env->check_sign = 1;
	if ((!check_before(str, c1->i - 1, '>')
	&& !check_before(str, c1->i - 1, '|')) ||
(check_before(str, c1->i - 1, '>') && check_before(str, c1->i - 1, '|')))
	{
		fd = open(red_name(str + c1->i + 1), O_CREAT | O_WRONLY
		| O_TRUNC, 0666);
		dup2(fd, 1);
		if (c1->res != NULL)
			ft_putstr_fd(red_cut(commands, env, c1->res), 1);
		else
			ft_putstr_fd(red_cut(commands, env,
check_exeption_chiante(c1->cop, str + c1->i + 1, "D")), 1);
		dup2(oldfd, 1);
		close(fd);
	}
	else
		sort_with_red(commands, env, str + c1->i + 1, c1->cop);
	if (ft_check_red(str + c1->i + 1, "<>|") == 0)
		while (str[c1->i + 1] && ft_check_red_char(str[c1->i + 1], "<>|") != 1)
			(c1->i)++;
}

void	ft_red_norm2(char *str, t_comp *c1, t_list *commands, t_env *env)
{
	int fd;
	int oldfd;

	oldfd = dup(1);
	env->check_sign = 1;
	if ((!check_before(str, c1->i - 1, '>') &&
!check_before(str, c1->i - 1, '|')) || (check_before(str, c1->i - 1, '>')
	&& check_before(str, c1->i - 1, '|')))
	{
		fd = open(red_name(str + c1->i + 2), O_CREAT | O_WRONLY
	| O_APPEND, 0666);
		dup2(fd, 1);
		if (c1->res != NULL)
			ft_putstr_fd(red_cut(commands, env, c1->res), 1);
		else
			ft_putstr_fd(red_cut(commands, env, c1->cop), 1);
		dup2(oldfd, 1);
		close(fd);
	}
	else
		sort_with_red(commands, env, str + c1->i + 2, c1->cop);
	(c1->i)++;
	if (ft_check_red(str + c1->i + 1, "<>|") == 0)
		while (str[c1->i + 1] && ft_check_red_char(str[c1->i + 1], "<>|") != 1)
			(c1->i)++;
}

void	ft_red_norm3(t_comp *c1, t_list *commands, t_env *env, char *str)
{
	char *string;

	if (c1->res != NULL)
		c1->res = ft_strjoin(c1->res, sort_with_red(commands,
		env, c1->cop, str + c1->i + 1));
	else
	{
		string = sort_with_red(commands, env, c1->cop, str + c1->i + 1);
		c1->res = string;
	}
	while (str[c1->i] && str[c1->i + 1] && ft_check_red(str + c1->i + 1,
	"<>|") != 0 && ft_check_red_char(str[c1->i + 1], "<>|") != 1)
		(c1->i)++;
	if (ft_check_red(str + c1->i + 1, "<>|") == 0)
		c1->res = red_cut(commands, env, c1->res);
}

int		ft_red_norm4(t_comp *c1, char *str, char **copy, t_env *env)
{
	c1->j = 0;
	c1->i = 0;
	c1->res = NULL;
	env->check_sign = 0;
	if (!((*copy) = malloc((ft_strlen(str) + 1) * sizeof(char))))
		return (1);
	return (0);
}
