/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:37:25 by abourin           #+#    #+#             */
/*   Updated: 2020/02/29 16:56:06 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_army_if_norm1(t_env *env, char *cop,
							char *str, t_list *command)
{
	if (ft_strncmp(cop, "echo", 5) == 0)
		command->result = echo_main(env, str);
	else if (ft_strncmp(cop, "exit", 5) == 0)
		command->result = str;
	else if (is_command_path_to_file(cop) != -1)
	{
		if (is_command_path_to_file(cop) == 2)
			printf_error(env->prog_name, 0, "is a directory", cop);
		else
			command->result = execute_binary_file(cop, remove_quote_arg(str),
				env);
	}
	else if (command_path_to_file_with_env(cop, env) == 0)
		command->result = execute_env_binary_file(cop, remove_quote_arg(str),
				env);
	else
		printf_error(env->prog_name, 0, str, "Command not found");
}

void			ft_army_if(t_env *env, char *cop, char *str, t_list *command)
{
	if (cop[0] == 34 || cop[0] == 39)
	{
		str++;
		cop++;
	}
	env->check = 0;
	if (ft_strncmp(cop, "cd", 3) == 0)
	{
		cd_split(env, str);
		command->result = NULL;
	}
	else if (ft_strncmp(cop, "export", 7) == 0)
	{
		command->result = export_env(env, cop, remove_quote_arg(str));
	}
	else if (ft_strncmp(cop, "env", 4) == 0)
		command->result = display_env_list(env);
	else if (ft_strncmp(cop, "unset", 6) == 0)
		unset(env, cop, str);
	else if (ft_strncmp(cop, "pwd", 4) == 0)
		command->result = pwd(env, str);
	else
		ft_army_if_norm1(env, cop, str, command);
}
