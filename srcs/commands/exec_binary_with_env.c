/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_with_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:33:13 by abourin           #+#    #+#             */
/*   Updated: 2020/02/26 10:45:01 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_full_path(char *path, t_env *env)
{
	t_env_variable	*path_env;
	int				len;
	char			*full_path;
	char			**paths;
	int				i;

	if (!(path_env = get_env_variable_if_exist(env->env_variables, "PATH")))
		return (NULL);
	i = 0;
	paths = ft_split(path_env->content, ':');
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		full_path = ft_strjoin(
			paths[i][len] != '/' ? ft_strjoin(paths[i], "/")
			: paths[i], path);
		free(paths[i]);
		paths[i] = full_path;
		i++;
	}
	return (paths);
}

int		command_path_to_file_with_env(char *path, t_env *env)
{
	char			**full_paths;
	int				i;

	i = 0;
	full_paths = get_env_full_path(path, env);
	while (full_paths && full_paths[i])
	{
		if (is_command_path_to_file(full_paths[i]) == 0)
		{
			free(full_paths);
			return (0);
		}
		free(full_paths[i]);
		i++;
	}
	free(full_paths);
	return (-1);
}

int		get_env_list_size(t_env_variable *variables)
{
	int		nb;

	nb = 0;
	while (variables)
	{
		nb++;
		variables = variables->next;
	}
	return (nb);
}

char	*execute_env_binary_file2(t_env *env, char **t, char *path, int i)
{
	int error;

	error = execve(env->full_paths[i], env->ac, t);
	error == -1 ? printf_error("Minishell", errno, path, NULL) : 0;
	return (NULL);
}

char	*execute_env_binary_file(char *binary, char *path, t_env *env)
{
	int				i;
	char			**t;
	pid_t			pid;

	env->ac = get_function_args(path);
	if (exec_binary_norm(&t))
		return (NULL);
	i = 0;
	env->full_paths = get_env_full_path(binary, env);
	while (env->full_paths[i])
	{
		if (is_command_path_to_file(env->full_paths[i]) == 0)
		{
			pid = fork();
			if (pid == 0)
				return (execute_env_binary_file2(env, t, path, i));
			else
				waitpid(pid, &(env->last_program_return), 0);
			ft_free(t);
			return (NULL);
		}
		i++;
	}
	ft_free(t);
	return (NULL);
}
