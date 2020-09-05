/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middleware.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:12:05 by abourin           #+#    #+#             */
/*   Updated: 2020/02/29 11:32:13 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_check_red_char(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void		execute_commands(t_list *commands, t_env *env)
{
	t_list	*tmp;

	tmp = commands;
	while (tmp)
	{
		if (ft_check_red(tmp->content, "<>|") == 1)
			ft_red(commands, env, tmp->content);
		else
		{
			ft_sort(env, tmp);
			if (env->check == 42)
				tmp->separator = (void *)42;
			else
				tmp->separator = 0;
		}
		tmp = tmp->next;
	}
	display_commands_result(commands);
}

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

int				ft_check_red(char *str, char *sep)
{
	t_comp all;

	all.exp_1 = -1;
	all.exp_2 = -1;
	all.exp_3 = -1;
	all.i = 0;
	while (str[all.i])
	{
		if (ft_norm_check_red(&all, str) == 0)
			return (0);
		all.j = 0;
		while (sep[all.j])
		{
			if (str[all.i] == sep[all.j] &&
			all.exp_1 < 0 && all.exp_2 < 0 && all.exp_3 < 0)
				return (1);
			all.j++;
		}
		all.i++;
		if (all.exp_3 > 0)
			all.exp_3 *= -1;
	}
	return (0);
}

void			command_middleware(t_env *env, char *input)
{
	t_list		*comm_list;
	t_list		*curr;
	char		**commands;
	int			i;

	if (!(comm_list = malloc(sizeof(t_list))))
		return ;
	commands = ft_split_modif(input, ';');
	comm_list->content = commands[0] ? commands[0] : NULL;
	comm_list->next = NULL;
	comm_list->result = NULL;
	i = 1;
	if (commands[0] == NULL)
	{
		env->last_program_return = 0;
		return ;
	}
	while (commands[i])
	{
		curr = ft_lstnew(commands[i]);
		curr->result = NULL;
		ft_lstadd_back(&comm_list, curr);
		i++;
	}
	execute_commands(comm_list, env);
}
