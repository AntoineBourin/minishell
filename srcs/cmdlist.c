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
