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
