/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:20:08 by abourin           #+#    #+#             */
/*   Updated: 2020/02/10 17:44:31 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_command_path_to_file(char *path)
{
	struct stat		sb;
	int				res;
	
	res = stat(path, &sb);
	return (S_ISDIR(sb.st_mode) ? 2 : res);
}

char	*execute_binary_file(char *path, char *args, t_env *env)
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
		return (NULL);
	}
	else
	{
		waitpid(pid, &(env->last_program_return), 0);
		return (NULL);
	}
	return (NULL);
}
