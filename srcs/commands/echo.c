/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:06:25 by nveron            #+#    #+#             */
/*   Updated: 2020/02/05 11:14:04 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
int     check_arg_n(char *str)
{
    int i;
    int a;
    a = 0;
    i = 0;
    while (str[i] == ' ')
        i++;
    i += 5;
    while (str[i] == ' ')
        i++;
    while (str[i])
    {
        if (a == 0 && str[i] != '-')
                return (0);
        if (a == 1 && str[i] != 'n')
                return (0);
        if (a == 2 && str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r' && str[i] != '\v' && str[i] != '\f' && str[i] != '\0')
                return (0);
        if (a == 3)
            return (i);
        a++;
        i++;
    }
    if (a >= 2 && str[i - 1] == 'n' && str[i - 2] == '-')
        return (i);
    return (0);
}
char    *echo_main(t_env *env, char *str)
{
    int i;
    int j;
    char *ret;

    i = 0;
    j = 0;
    if (!(ret = malloc (ft_strlen(str) + 1)))
        return (NULL);
    while (str[i] == ' ')
        i++;
    if (check_arg_n(str) > 0)
    {
        i += check_arg_n(str);
        env->check = 42;
    }
    else
        i += 5;
    while (str[i] == ' ')
        i++;
    while (str[i])
    {
        if (str[i] != '"' && str[i] != 39)
        {    
            ret[j] = str[i];
            j++;
        }
       i++;
    }
    ret[j] = '\0';
    if (ret[0] == '\0')
        return (NULL);
    return (ret);
}