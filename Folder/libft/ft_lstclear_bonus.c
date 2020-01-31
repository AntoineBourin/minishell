/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 10:51:27 by nveron            #+#    #+#             */
/*   Updated: 2019/10/22 14:25:39 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *last;
	t_list *prev;

	prev = *lst;
	prev = prev->next;
	last = *lst;
	while (prev->next)
	{
		(*del)(last);
		free(last);
		last = prev;
		prev = prev->next;
	}
}
