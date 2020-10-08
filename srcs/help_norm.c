/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:58:05 by cnotin            #+#    #+#             */
/*   Updated: 2020/10/04 22:16:08 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		error_semi_norm(t_env *env)
{
	ft_putstr_fd("minishell : ", 1);
	ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
	env->last_program_return = 1;
}

void		command_read_norm_free(t_env *env, char **str)
{
	ft_free(str);
	free(env->ac);
}

int			help_error(char *s, t_env *env)
{
	if (!ft_error_semi(s, env))
	{
		env->last_program_return = 1;
		return (0);
	}
	if (search_pipe(s, '|') || !error_redir(s, env) || !again(s) || !again_3(s))
	{
		env->last_program_return = 1;
		return (0);
	}
	return (1);
}

int			len_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char		*fill_path(char **paths, int i, char *cmd)
{
	char	*full_path;

	if (!(full_path = malloc(sizeof(char) * (ft_strlen(paths[i]) +
			ft_strlen(cmd) + 4))))
		return (NULL);
	full_path = ft_strcpy(full_path, paths[i]);
	full_path = ft_strcat(full_path, "/");
	full_path = ft_strcat(full_path, cmd);
	return (full_path);
}
