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

int     check_if_char_in_str_is_in_str2(char *charset, char *str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (charset[j] == str[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int     cut_cmd_for_pipe_and_redirection_malloc(char ***ac, char *str)
{
	int i;

	i = 0;
	if (!(*ac = malloc(sizeof(char*) * 4)))
		return (1);
	while (str[i] && check_if_char_is_in_str_modif(str[i], str, "<>|", i) != 1)
		i++;
	if (!((*ac)[0] = malloc(sizeof(char) * (i + 1))))
		return (1);
	if (!((*ac)[1] = malloc(sizeof(char) * (3))))
		return (1);
	str += i;
	i = 0;
	while (str[i] && check_if_char_is_in_str_modif(str[i], str, "<>|", i) == 1)
		i++;
	str += i;
	i = 0;
	while (str[i] && check_if_char_is_in_str_modif(str[i], str, "<>|", i) != 1)
		i++;
	if (!((*ac)[2] = malloc(sizeof(char) * (i + 1))))
		return (1);
	(*ac)[3] = NULL;
	return (0);
}

int     cut_cmd_for_pipe_and_redirection_norme1(char *str, char **ac, int j, int x)
{
	int i;
	int e;
	char *cpy;

	i = 0;
	e = 1;
	cpy = NULL;
	if (j)
	{
		while (*str == ' ')
			str++;
		cpy = str;
		while ((str)[i] && check_if_char_is_in_str_modif((str)[i], cpy, "<>|", i) != 1)
		{
			ac[x][i] = (str)[i];
			i++;
		}
		ac[x][i] = '\0';
		while (i - e >= 0 && ac[x][i - e] == ' ')
		{
			ac[x][i - e] = '\0';
			e++;
		}
	}
	else
	{
		cpy = str;
		while ((str)[i] && check_if_char_is_in_str_modif((str)[i], cpy, "<>|", i) == 1)
		{
			ac[x][i] = (str)[i];
			i++;
		}
		ac[x][i] = '\0';
	}
	return (i);
}

char **cut_cmd_for_pipe_and_redirection(char **str)
{
	int i;
	char **ac;

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

void    ft_free_ac(char **ac)
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

t_fdlist	*fdlist_new(int fd)
{
	t_fdlist	*new;

	new = (t_fdlist *)malloc(sizeof(t_fdlist));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	return (new);
}

void		fdlist_clear(t_fdlist **lst)
{
	t_fdlist	*temp;
	t_fdlist	*iter;

	if (!lst || !(*lst))
		return ;
	iter = *lst;
	while (iter)
	{
		temp = iter->next;
		close(iter->fd);
		free(iter);
		iter = temp;
	}
	*lst = NULL;
	lst = NULL;
}

void		fdlist_print(t_fdlist *lst)
{
	while (lst)
	{
		ft_putnbr_fd(lst->fd, 1);
		ft_putstr_fd("-->", 1);
		lst = lst->next;
	}
	ft_putstr_fd("(NULL)\n", 1);
}

void		fdlist_add_back(t_fdlist **alst, t_fdlist *new)
{
	t_fdlist	*lst;

	lst = *alst;
	if (!lst)
		*alst = new;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}


t_cmdlist	*cmdlist_new(void *command)
{
	t_cmdlist	*new;

	new = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	if (!new)
		return (NULL);
	new->command = command;
	new->fd_in = NULL;
	new->fd_out = NULL;
	new->fd_out_err = NULL;
	new->next = NULL;
	return (new);
}

void		cmdlist_clear(t_cmdlist **lst, void (*del)(void *))
{
	t_cmdlist	*temp;
	t_cmdlist	*iter;

	if (!lst || !(*lst))
		return ;
	iter = *lst;
	while (iter)
	{
		temp = iter->next;
		del(iter->command);
		fdlist_clear(&(iter->fd_in));
		fdlist_clear(&(iter->fd_out));
		fdlist_clear(&(iter->fd_out_err));
		free(iter);
		iter = temp;
	}
	*lst = NULL;
	lst = NULL;
}

void		cmdlist_print(t_cmdlist *lst)
{
	ft_putstr_fd("displaying cmdlist:\n", 1);
	while (lst)
	{
		ft_putstr_fd("cmd = ", 1);
		ft_putstr_fd(lst->command, 1);
		ft_putstr_fd("\nfd_in = : ", 1);
		fdlist_print(lst->fd_in);
		ft_putstr_fd("\nfd_out = : ", 1);
		fdlist_print(lst->fd_out);
		ft_putstr_fd("\nfd_out_err = : ", 1);
		fdlist_print(lst->fd_out_err);
		ft_putstr_fd("\n-->", 1);
		lst = lst->next;
	}
	ft_putstr_fd("(NULL)\n", 1);
}

void		cmdlist_add_back(t_cmdlist **alst, t_cmdlist *new)
{
	t_cmdlist	*lst;

	lst = *alst;
	if (!lst)
		*alst = new;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

void    fill_fd(t_cmdlist *list, char **ac, t_env *env)
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
		new_fd = fdlist_new(open(ac[2], O_RDONLY, 0666));
		fdlist_add_back(&list->fd_in, new_fd);
		env->check_fd_in = 1;
	}
}

char *ft_cpy(char *str)
{
	char *new;
	int i;

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

t_cmdlist *fill_list(t_env *env, char **ac, char *str)
{
	t_cmdlist *list;

	list = cmdlist_new(NULL);
	env->check_fd_in = 0;
	env->check_fd_out = 0;
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

void    redirection(char *str, int fd_in, int fd_out, t_env *env)
{
	pid_t		prog_id;

	prog_id = fork();
	if (prog_id == 0)
	{
		dup2(fd_in, 0);
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

void		exec_cmd_redirection_list(t_fdlist *lst, t_cmdlist *list_2, t_env *env)
{
	while (lst)
	{
		redirection(list_2->command, lst->fd, list_2->fd_out->fd, env);
		lst = lst->next;
	}
}

void    exec_cmd_redirection(t_cmdlist **list, t_env *env)
{
	t_cmdlist *list_2;

	list_2 = *list;
	while (list_2->fd_out)
	{
		exec_cmd_redirection_list(list_2->fd_in, list_2, env);
		list_2->fd_out = list_2->fd_out->next;
	}
}

int    ft_pipe(char *str, t_env *env, int *fd, int check)
{
	static int	fd_in;
	pid_t		prog_id;

	if (!check)
		fd_in = 0;
	fd_in = (!fd_in) ? 0 : fd_in;
	prog_id = fork();
	if (prog_id == 0)
	{
		dup2(fd_in, 0);
		if (env->ope_type == 1)
		{
			dup2(fd[1], 1);
			close(fd[1]);
		}
		else if (env->ope_type > 1 && env->ope_type != -1)
		{
			dup2(env->ope_type, 1);
			close(env->ope_type);
			dup2(-1, 1);
		}
		else
			dup2(-1, 1);
		command_read(str, env);
		exit(env->last_program_return);
		fd_in = 0;
	}
	else
	{
		wait(&prog_id);
		env->last_program_return = WEXITSTATUS(prog_id);
		close(fd[1]);
		fd_in = fd[0];
	}

	return (1);
}

void    pipe_select(int fd_out, char *str, t_env *env)
{
	char **ac;
	int check;
	int fd[2];

	pipe(fd);
	ac = NULL;
	check = 0;
	ac = cut_cmd_for_pipe_and_redirection(&str);
	if (ac[1][0] == '|')
	{
		env->ope_type = 1;
		check = ft_pipe(ac[0], env, fd, check);
		if (check_if_char_in_str_is_in_str2("|", str))
			env->ope_type = 1;
		else
			if (fd_out == 1)
				env->ope_type = 0;
			else
				env->ope_type = fd_out;
		pipe(fd);
		check = ft_pipe(ac[2], env, fd, check);
	}
	while (check_if_char_in_str_is_in_str2("|", str))
	{
		ft_free_ac(ac);
		pipe(fd);
		ac = cut_cmd_for_pipe_and_redirection(&str);
		if (check_if_char_in_str_is_in_str2("|", str))
			env->ope_type = 1;
		else
		{
			if (fd_out == 1)
				env->ope_type = 0;
			else
				env->ope_type = fd_out;
		}
		check = ft_pipe(ac[2], env, fd, check);
	}
}


void    exec_cmd_redirection_for_pipe(t_cmdlist **list, t_env *env, char *str)
{
	t_cmdlist *list_2;

	list_2 = *list;
	while (list_2->fd_out)
	{
		pipe_select(list_2->fd_out->fd, str, env);
		list_2->fd_out = list_2->fd_out->next;
	}
}

void    redirection_sort(char *str, t_env *env)
{
	char **ac;
	t_cmdlist *list;

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
