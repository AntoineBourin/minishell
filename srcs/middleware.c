/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middleware.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:12:05 by abourin           #+#    #+#             */
/*   Updated: 2020/02/04 14:20:47 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_army_if(t_env *env, char *cop, char *str)
{
	if (ft_strncmp(cop, "cd", 2) == 0)
		cd_split(env, str);
	else
		printf_error("Minishell", 0, str, "Command not found");
}

static void	ft_sort(t_env *env, char *str)
{
	char *cop;
	int i;
	int j;
	int tmp;

	j = 0;
	i = 0;
	if (!(cop = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return ;
	while (str[i] == ' ')
		i++;
	tmp = i;
	while (str[i] && str[i] != ' ' && str[i] != ';' && str[i] != '\n')
	{
		cop[j] = str[i];
		i++;
		j++;
	}
	cop[j] = '\0';
	ft_army_if(env, cop, str + tmp);
	free(cop);
	cop = NULL;
}

static void	execute_commands(t_list *commands, t_env *env)
{
	t_list	*tmp;

	tmp = commands;
	while (tmp)
	{
		ft_sort(env, tmp->content);
		tmp = tmp->next;
	}
}

void	command_middleware(t_env *env, char *input)
{
	t_list		*comm_list;
	t_list		*curr;
	char		**commands;
	int			i;

	if (!(comm_list = malloc(sizeof(t_list))))
		return ;
	commands = ft_split(input, ';');
	comm_list->content = commands[0] ? commands[0] : NULL;
	comm_list->next = NULL;
	i = 1;
	if (commands[0] == NULL)
		return ;
	while (commands[i])
	{
		curr = ft_lstnew(commands[i]);
		ft_lstadd_back(&comm_list, curr);
		i++;
	} 	
	execute_commands(comm_list, env);
}
