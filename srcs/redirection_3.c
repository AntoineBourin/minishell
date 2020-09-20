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

void		fill_fd(t_cmdlist *list, char **ac, t_env *env)
{
	t_fdlist	*new_fd;

	if (ac[1][0] == '>' && ac[1][1] == '\0')
	{
		close(open(ac[2], O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0666));
		new_fd = fdlist_new(open(ac[2], O_CREAT | O_WRONLY | O_APPEND, 0666));
		fdlist_add_back(&list->fd_out, new_fd);
		env->check_fd_out = 1;
	}
	else if (ac[1][0] == '>' && ac[1][1] && ac[1][1] == '>')
	{
		new_fd = fdlist_new(open(ac[2], O_CREAT | O_WRONLY | O_APPEND, 0666));
		fdlist_add_back(&list->fd_out, new_fd);
		env->check_fd_out = 1;
	}
	else if (ac[1][0] == '<')
	{
		new_fd = fdlist_new(check_error_open(list, ac[2]));
		fdlist_add_back(&list->fd_in, new_fd);
		env->check_fd_in = 1;
	}
}

char		*ft_cpy(char *str)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

t_cmdlist	*fill_list(t_env *env, char **ac, char *str)
{
	t_cmdlist *list;

	list = cmdlist_new(NULL);
	env->check_fd_in = 0;
	env->check_fd_out = 0;
	list->check_error = 0;
	ac = cut_cmd_for_pipe_and_redirection(&str);
	list->command = ft_cpy(ac[0]);
	fill_fd(list, ac, env);
	while (check_if_char_in_str_is_in_str2_modif("<>|", str))
	{
		ft_free_ac(ac);
		ac = cut_cmd_for_pipe_and_redirection(&str);
		fill_fd(list, ac, env);
	}
	if (!(env->check_fd_in))
		fdlist_add_back(&list->fd_in, fdlist_new(0));
	if (!(env->check_fd_out))
		fdlist_add_back(&list->fd_out, fdlist_new(1));
	return (list);
}

void		redirection(char *str, int fd_in, int fd_out, t_env *env)
{
	pid_t		prog_id;

	prog_id = fork();
	if (prog_id == 0)
	{
		dup2(fd_in, 0);
		if (command_path_to_file_with_env(
			command_name_with_or_without_quote(str), env) == 0)
			dup2(fd_out, 1);
		command_read(str, env);
		lseek(fd_in, 0, SEEK_SET);
		exit(env->last_program_return);
	}
	else
	{
		wait(&prog_id);
		env->last_program_return = WEXITSTATUS(prog_id);
	}
}

void		exec_cmd_redirection_list(t_fdlist *lst,
			t_cmdlist *list_2, t_env *env)
{
	while (lst)
	{
		redirection(list_2->command, lst->fd, list_2->fd_out->fd, env);
		lst = lst->next;
	}
}
