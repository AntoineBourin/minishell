/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/30 18:58:32 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*execute_binary_file(char *path, char *args, t_env *env)
{
	int		error;
	pid_t	pid;
	char	**ac;

	pid = fork();
	ac = get_function_args(args);
	if (pid == 0)
	{
		error = execve(path, ac, env->data_env);
		error == -1 ? printf_error("Minishell", errno, path, NULL) : 0;
		ft_free(ac);
		error == -1 ? exit(127) : exit(0);
	}
	else
	{
		wait(&pid);
		env->last_program_return = WEXITSTATUS(pid);
		return (NULL);
	}
	return (NULL);
}

char		*command_remove_quote_etc(char *str)
{
	char	*buff;
	char	*ref;
	char	*ref_str;
	int		presence_of_34;
	int		presence_of_39;

	presence_of_34 = -1;
	presence_of_39 = -1;
	if (!(buff = malloc(sizeof(char) * ft_strlen(str) + 2)))
		return (NULL);
	ref = buff;
	ref_str = str;
	while (*str)
	{
		command_remove_quote_etc_norm1(&str,
		ref_str, &presence_of_34, &presence_of_39);
		if (!(*str))
			break ;
		command_remove_quote_etc_norm2(&str, &buff);
	}
	*buff = '\0';
	return (ref);
}

void		command_read_norm1(char *buff, t_env *env, char *name_cmd)
{
	if (ft_strncmp(name_cmd, "env", 4) == 0)
		display_env_list(env);
	else if (ft_strncmp(name_cmd, "unset", 6) == 0)
		unset(env, name_cmd, command_remove_quote_etc(buff));
	else if (ft_strncmp(name_cmd, "export", 7) == 0)
		export_env(env, command_remove_quote_etc(buff));
	else if (ft_strncmp(name_cmd, "echo", 5) == 0)
		echo_main(buff, env->ac, env);
	else if (buff[0] != '\0' && command_path_to_file_with_env(
		name_cmd, env) == 0)
		execute_env_binary_file(name_cmd, buff, env);
	else if (is_command_path_to_file(name_cmd) != -1)
	{
		env->last_program_return = 1;
		if (is_command_path_to_file(name_cmd) == 2)
			printf_error(env->prog_name, 0, "is a directory", name_cmd);
		else
			execute_binary_file(name_cmd, remove_quote_arg(buff), env);
	}
	else
	{
		printf_error(env->prog_name, 0, command_remove_quote_etc(
			name_cmd), "Command not found");
		env->last_program_return = 127;
	}
}

void		command_read(char *buff, t_env *env)
{
	char *name_cmd;

	name_cmd = command_name_with_or_without_quote(buff);
	name_cmd = command_remove_quote_etc(name_cmd);
	if (buff[0] == '\0')
	{
		env->last_program_return = 0;
		return ;
	}
	else if (buff[0] != '\0' && check_if_quote_are_close(buff))
	{
		printf_error(env->prog_name, 0, buff, "Quote are not closed");
		env->last_program_return = 1;
		return ;
	}
	env->ac = get_function_args(buff);
	if (buff[0] != '\0' && ft_strncmp(name_cmd, "exit", 5) == 0)
		ft_exit(env);
	else if (ft_strncmp(name_cmd, "pwd", 4) == 0)
		pwd(env, buff);
	else if (ft_strncmp(name_cmd, "cd", 3) == 0)
		cd_split(env);
	else
		command_read_norm1(buff, env, name_cmd);
	command_read_norm_free(env, &name_cmd);
}

int			check_if_quote_are_close(char *str)
{
	int presence_of_34;
	int presence_of_39;

	presence_of_34 = -1;
	presence_of_39 = -1;
	while (*str)
	{
		if (*str == 34 && presence_of_39 < 0)
			presence_of_34 *= -1;
		if (*str == 39 && presence_of_34 < 0)
			presence_of_39 *= -1;
		if (presence_of_39 < 0 && presence_of_34 < 0)
			if (*str == 92 && *(str + 1) != '\0')
				str += 1;
		str++;
	}
	if (*(str - 1) == 92 && ft_strlen(str) > 1 && *(str - 2) != 92)
		return (1);
	if (presence_of_39 < 0 && presence_of_34 < 0)
		return (0);
	return (1);
}
