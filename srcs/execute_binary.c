/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:20:08 by abourin           #+#    #+#             */
/*   Updated: 2020/02/05 14:10:33 by abourin          ###   ########.fr       */
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

char	*execute_binary_file(char *path, char *args)
{
	int	error;

	error = execve(path, NULL, NULL);
	printf_error("Minishell", errno, path, NULL);
	return (NULL);
}
