/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/04 11:01:47 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_if_is_the_end_of_the_cmd(char *str, int i)
{
    if (str[i] && str[i] != ' ')
        return (0);
    while (str[i] && str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return (1);
    return (0);
}

void    echo_main(char *str, char **ac, t_env *env)
{
    int i;

    i = 0;
    if (ac[1] != '\0' && ft_strncmp(ac[1], "-n", 3) == 0)
    {
        while (str[i] != '-')
            i++;
        i += 2;
    }
    else
        i += 4;
    while (str[i] == ' ')
        i++;
    while (str[i])
    {
        if (!(check_if_is_the_end_of_the_cmd(str, i)))
            ft_putchar_fd(str[i], 1);
        i++;
    }
    if (ft_strncmp(ac[1], "-n", 3) != 0)
        ft_putchar_fd('\n', 1);
    env->last_program_return = 0;
}