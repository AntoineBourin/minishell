/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middleware.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:12:05 by abourin           #+#    #+#             */
/*   Updated: 2020/02/29 16:19:54 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_sort(t_env *env, t_list *command)
{
	int		tmp;
	char	*cop;
	char	*str;
	t_comp	c1;

	c1.j = 0;
	c1.i = 0;
	c1.exp_1 = -1;
	c1.exp_2 = -1;
	str = command->content;
	if (!(cop = malloc(sizeof(char) * (ft_strlen(str) + 3))))
		return ;
	ft_sort_norm1(&c1, str, &tmp);
	while (str[c1.i] && ((c1.exp_1 > 0 || c1.exp_2 > 0) ||
				(str[c1.i] != ' ' && str[c1.i] != '\n')))
		ft_sort_norm2(&c1, &str, &cop);
	cop[c1.j] = '\0';
	if (c1.exp_1 > 0 || c1.exp_2 > 0)
		cop = ft_strjoin(ft_strjoin(" ", "'"), cop);
	ft_army_if(env, cop, str + tmp, command);
	free(cop);
	cop = NULL;
}

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

int				ft_check_red(char *str, char *sep)
{
	int	i;
	int	j;
	int	exp_1;
	int	exp_2;

	exp_1 = -1;
	exp_2 = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
			exp_1 *= -1;
		if (str[i] == 34)
			exp_2 *= -1;
		j = 0;
		while (sep[j])
		{
			if (str[i] == sep[j] && exp_1 < 0 && exp_2 < 0)
				return (1);
			j++;
		}
		i++;
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
		return ;
	while (commands[i])
	{
		curr = ft_lstnew(commands[i]);
		curr->result = NULL;
		ft_lstadd_back(&comm_list, curr);
		i++;
	}
	execute_commands(comm_list, env);
}
