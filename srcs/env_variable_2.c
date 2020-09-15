/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/15 16:31:07 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_free(char **str)
{
	if (*str)
		free(*str);
	(*str) = NULL;
}

void			printf_error(char *name, int error, char *str, char *errorstr)
{
	ft_putstr_fd(name, 1);
	ft_putstr_fd(": ", 1);
	if (error != 0)
		ft_putstr_fd(strerror(error), 1);
	else
		ft_putstr_fd(errorstr, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
}

t_env_variable	*get_env_variable_if_exist(t_env_variable *env_variables,
		char *name)
{
	while (env_variables)
	{
		if (env_variables->name
				&& ft_strncmp(env_variables->name, name, ft_strlen(name)) == 0)
			return (env_variables);
		env_variables = env_variables->next;
	}
	return (NULL);
}

char			**get_env_full_path(char *path, t_env *env)
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

int				command_path_to_file_with_env(char *path, t_env *env)
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
