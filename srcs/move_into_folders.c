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

void    move_init(t_env *env)
{
    int check_error;
	char *buff;
    (void)env;

    check_error = chdir("/Users/");
	buff = NULL;
    buff = getcwd(buff, 1000000);

    if (!(env->curr_path = malloc(sizeof(char) * ft_strlen(buff))))
	    return ;
    env->curr_path = buff;
}

void    move(char *str, int pwd, t_env *env)
{
	int check_error;
	char *buff;
    (void)env;

	buff = NULL;
    buff = getcwd(buff, 1000000);
    if (pwd != 0 && str == NULL)
	    ft_putstr_fd(buff, 1);
    if (pwd == 0 && str != NULL)
    {
	    check_error = chdir(str);
        buff = getcwd(buff, 1000000);
        if (check_error != 0)
            ft_putstr_fd(strerror(ENOTDIR), 1);
        free(env->curr_path);
        env->curr_path = NULL;
        if (!(env->curr_path = malloc(sizeof(char) * ft_strlen(buff))))
		    return ;
        env->curr_path = buff;
    }	
}