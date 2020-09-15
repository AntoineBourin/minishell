/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/10 16:42:10 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**cut_cmd_for_pipe_and_redirection(char **str)
{
	int		i;
	char	**ac;

	ac = NULL;
	if (cut_cmd_for_pipe_and_redirection_malloc(&ac, *str))
		return (NULL);
	i = cut_cmd_for_pipe_and_redirection_norme1(*str, ac, 1, 0);
	(*str) += i;
	i = cut_cmd_for_pipe_and_redirection_norme1(*str, ac, 0, 1);
	(*str) += i;
	i = cut_cmd_for_pipe_and_redirection_norme1(*str, ac, 1, 2);
	while (**str == ' ')
		(*str)++;
	return (ac);
}

void		ft_free_ac(char **ac)
{
	if (ac == NULL)
		return ;
	if (ac[0])
	{
		free(ac[0]);
		ac[0] = NULL;
	}
	if (ac[1])
	{
		free(ac[1]);
		ac[1] = NULL;
	}
	if (ac[2])
	{
		free(ac[2]);
		ac[2] = NULL;
	}
	if (ac)
	{
		free(ac);
		ac = NULL;
	}
}

void		pipe_select(int fd_out, char *str, t_env *env)
{
	char	**ac;
	int		check;
	int		fd[2];

	pipe(fd);
	check = 0;
	ac = cut_cmd_for_pipe_and_redirection(&str);
	if (ac[1][0] == '|')
	{
		env->ope_type = 1;
		check = ft_pipe(ac[0], env, fd, check);
		pipe_select_norm2(env, str, fd_out);
		pipe(fd);
		check = ft_pipe(ac[2], env, fd, check);
	}
	while (check_if_char_in_str_is_in_str2("|", str))
	{
		pipe(fd);
		ft_free_ac(ac);
		ac = cut_cmd_for_pipe_and_redirection(&str);
		pipe_select_norm1(env, str, fd_out);
		check = ft_pipe(ac[2], env, fd, check);
	}
}

void		exec_cmd_redirection_for_pipe(t_cmdlist **list,
			t_env *env, char *str)
{
	t_cmdlist *list_2;

	list_2 = *list;
	while (list_2->fd_out)
	{
		pipe_select(list_2->fd_out->fd, str, env);
		list_2->fd_out = list_2->fd_out->next;
	}
}

void		redirection_sort(char *str, t_env *env)
{
	char		**ac;
	t_cmdlist	*list;

	ac = NULL;
	list = fill_list(env, ac, str);
	if (check_if_char_in_str_is_in_str2("|", str))
	{
		exec_cmd_redirection_for_pipe(&list, env, str);
	}
	else
	{
		exec_cmd_redirection(&list, env);
	}
}
