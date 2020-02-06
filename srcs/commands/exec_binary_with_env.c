/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_with_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:33:13 by abourin           #+#    #+#             */
/*   Updated: 2020/02/06 15:05:34 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_full_path(char *path, t_env *env)
{
	t_env_variable	*path_env;
	int				len;
	char			*full_path;

	if (!(path_env = get_env_variable_if_exist(env->env_variables, "PATH")))
		return (NULL);
	len = ft_strlen(path_env->content);
	full_path = ft_strjoin(
		path_env->content[len] != '/' ? ft_strjoin(path_env->content, "/")
		: path_env->content, path);
	return (full_path);
}

int		command_path_to_file_with_env(char *path, t_env *env)
{
	char			*full_path;

	full_path = get_env_full_path(path, env);
	return (is_command_path_to_file(full_path) == 2 ? 0
			: is_command_path_to_file(full_path));
}

char	*execute_env_binary_file(char *path, t_env *env)
{
	char			*full_path;

	full_path = get_env_full_path(path, env);
	execve(full_path, NULL, NULL);
	return (NULL);
}
