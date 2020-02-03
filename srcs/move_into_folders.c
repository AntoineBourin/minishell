/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_into_folder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:06:25 by nveron            #+#    #+#             */
/*   Updated: 2020/02/03 13:08:38 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    move(char *str, int pwd)
{
	int check_error;
	char *buff;

	buff = NULL;
    if (pwd != 0 && str == NULL)
	    ft_putstr_fd(getcwd(buff, 1000000), 1);
    if (pwd == 0 && str != NULL)
    {
	    check_error = chdir(str);
        if (check_error != 0)
        {
            ft_putstr_fd(strerror(ENOTDIR), 1);

        }
    }
	
}