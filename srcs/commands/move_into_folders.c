/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_into_folders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:06:25 by nveron            #+#    #+#             */
/*   Updated: 2020/02/26 12:12:53 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_error(char *name, int error, char *str, char *errorstr)
{
	ft_putstr_fd(name, 0);
	ft_putstr_fd(": ", 0);
	if (error != 0)
		ft_putstr_fd(strerror(error), 0);
	else
		ft_putstr_fd(errorstr, 0);
	ft_putstr_fd(": ", 0);
	ft_putstr_fd(str, 0);
	ft_putchar_fd('\n', 0);
}

void	replace_tild_by_home(char **str, t_env *env)
{
	t_env_variable	*home;
	int				i;

	i = 0;
	if (!(home = get_env_variable_if_exist(env->env_variables, "HOME")))
		return ;
	home->name = "~";
	while ((*str)[i])
	{
		if ((*str)[i] == '~')
			replace_env_name_by_value(str, home, i, i);
		i++;
	}
	home->name = "HOME";
}

void	remove_quote_arg2(int *check34, int *check39, int *i, char *str)
{
	(*i) = 0;
	(*check34) = 0;
	(*check39) = 0;
	while (str[(*i)])
	{
		if (str[(*i)] == 34)
			(*check34)++;
		if (str[(*i)] == 39)
			(*check39)++;
		(*i)++;
	}
	(*i) = 0;
	if ((*check34) % 2 != 0)
		(*check34)--;
	if ((*check39) % 2 != 0)
		(*check39)--;
}

char	*remove_quote_arg(char *str)
{
	t_quote q;

	if (!(q.copy = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	remove_quote_arg2(&(q.check34), &(q.check39), &(q.i), str);
	q.j = 0;
	while (str[q.i])
	{
		if ((str[q.i] == 39 && q.check39 > 0)
				|| (str[q.i] == 34 && q.check34 > 0))
		{
			q.check34 = str[q.i] == 34 ? q.check34 - 1 : q.check34;
			q.check39 = str[q.i] == 39 ? q.check39 - 1 : q.check39;
			(q.i)++;
		}
		else
		{
			(q.copy)[q.j] = str[q.i];
			(q.j)++;
			(q.i)++;
		}
	}
	(q.copy)[q.j] = '\0';
	return ((q.copy));
}

void	move(char *str, int pwd, t_env *env)
{
	int		check_error;
	char	*buff;
	int		i;

	i = 0;
	buff = NULL;
	if (str == NULL && pwd == 0)
		move_init(env);
	if (str == NULL && pwd == 0)
		return ;
	while (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\r' || *str == '\v' || *str == '\f')
		str++;
	str = remove_quote_arg(str);
	replace_tild_by_home(&str, env);
	buff = getcwd(buff, 1000000);
	check_error = chdir(str);
	buff = getcwd(buff, 1000000);
	if (check_error != 0)
		printf_error("cd", ENOENT, str, NULL);
	free(env->curr_path);
	env->curr_path = NULL;
	if (!(env->curr_path = malloc(sizeof(char) * ft_strlen(buff))))
		return ;
	env->curr_path = buff;
}
