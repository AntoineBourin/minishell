/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/10/01 13:32:34 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				get_env_list_size(t_env_variable *variables)
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

char			*execute_env_binary_file2(t_env
*env, char **t, char *path, int i)
{
	int error;

	error = execve(env->full_paths[i], env->ac, t);
	error == -1 ? printf_error("Minishell", errno, path, NULL) : 0;
	return (NULL);
}

char			*execute_env_binary_file(char *binary, char *path, t_env *env)
{
	int				i;
	char			**t;
	pid_t			pid;

	t = NULL;
	t = exec_binary_norm(t);
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
			free_tab(t, env->full_paths);
			return (NULL);
		}
		i++;
	}
	free_tab(t, env->full_paths);
	return (NULL);
}

void			move_init(t_env *env)
{
	int				check_error;
	char			*buff;
	char			*ret;
	t_env_variable	*home;

	home = get_env_variable_if_exist(env->env_variables, "HOME");
	if (home && home->content)
		check_error = chdir(home->content);
	else
		check_error = chdir("/Users");
	buff = NULL;
	ret = getcwd(buff, 1000000);
	free(buff);
	env->curr_path = ft_strdup(ret);
	free(ret);
}

char			*get_arg_quotes(char *arg, char charset)
{
	int		is_quoted;
	int		i;

	i = 0;
	if (arg && arg[0] && arg[0] == '"')
		is_quoted = 1;
	if (arg && arg[0] && arg[0] == '"')
		i++;
	else
		is_quoted = 0;
	while (arg && arg[i])
	{
		if ((arg[i] == charset) || (arg[i] == ' ' && !is_quoted))
		{
			arg[i] = '\0';
			return (arg);
		}
		if (arg[i] == '"' && is_quoted)
		{
			arg[i] = '\0';
			return (arg + 1);
		}
		i++;
	}
	return (arg);
}
