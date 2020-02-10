/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middleware.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:12:05 by abourin           #+#    #+#             */
/*   Updated: 2020/02/10 15:46:06 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_army_if(t_env *env, char *cop, char *str, t_list *command)
{
	env->check = 0;
	if (ft_strncmp(cop, "cd", 2) == 0)
	{
		cd_split(env, str);
		command->result = NULL;
	}
	else if (ft_strncmp(cop, "export", 6) == 0)
	{
		export_env(env, cop, str);
		command->result = NULL;
	}
	else if (ft_strncmp(cop, "env", 3) == 0)
		command->result = display_env_list(env);
	else if (ft_strncmp(cop, "unset", 5) == 0)
		unset(env, cop, str);
	else if (ft_strncmp(cop, "pwd", 3) == 0)
		command->result = pwd(env, str);
	else if (ft_strncmp(cop, "echo", 4) == 0)
		command->result = echo_main(env, str);
	else if (ft_strncmp(cop, "exit", 4) == 0)
		command->result = "exit";
	else if (is_command_path_to_file(cop) != -1)
	{
		if (is_command_path_to_file(cop) == 2)
			printf_error(env->prog_name, 0, "is a directory", cop);
		else
			command->result = execute_binary_file(cop, str, env);
	}
	else if (command_path_to_file_with_env(cop, env) == 0)
		command->result = execute_env_binary_file(cop, str, env);
	else
		printf_error(env->prog_name, 0, str, "Command not found");
}

static void	ft_sort(t_env *env, t_list *command)
{
	char 	*cop;
	int 	i;
	int 	j;
	int 	tmp;
	char	*str;

	j = 0;
	i = 0;
	str = command->content;
	if (!(cop = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return ;
	while (str[i] == ' ')
		i++;
	tmp = i;
	while (str[i] && str[i] != ' '
	&& str[i] != ';' && str[i] != '\n')
	{
		cop[j] = str[i];
		i++;
		j++;
	}
	cop[j] = '\0';
	ft_army_if(env, cop, str + tmp, command);
	free(cop);
	cop = NULL;
}
int 	ft_check_red_char(char c, char *str)
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

static void	execute_commands(t_list *commands, t_env *env)
{
	t_list	*tmp;

	tmp = commands;
	while (tmp)
	{
		if (ft_check_red(tmp->content) == 1)
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

int 	ft_check_red(char *str)
{
	int i;
	int j;
	char *sep;

	i = 0;
	sep = "<>|";
	while (str[i])
	{
		j = 0;
		while (sep[j])
		{
			if (str[i] == sep[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
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
