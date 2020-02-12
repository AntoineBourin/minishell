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
    while (str[i] && str[i] == ' ')
        i++;
    i += 4;
    while (str[i] && str[i] == ' ')
        i++;
    while (str[i])
    {
        if (a == 0 && str[i] != '-')
                return (0);
        if (a == 1 && str[i] != 'n')
                return (0);
        if (a == 2 && str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r' && str[i] != '\v' && str[i] != '\f')
                return (0);
        if (a == 3)
            return (i);
        a++;
        i++;
    }
    if (a >= 2)
    {
        while (str[i - 1] && str[i - 1] == ' ')
            i--;
        if (str[i - 1] == 'n' && str[i - 2] == '-')
            return (i);
    }
    return (0);
}
char    *echo_main(t_env *env, char *str)
{
    int i;
    int j;
    char *ret;

    i = 0;
    j = 0;
    env->check = 0;
    if (!(ret = malloc (ft_strlen(str) + 2)))
        return (NULL);
    while (str[i] && str[i] == ' ')
        i++;
    if (check_arg_n(str) > 0)
    {
        i += check_arg_n(str);
        env->check = 42;
    }
    else
        i += 4;
    while (str[i] && str[i] == ' ')
        i++;
    while (str[i] && str[i])
    {
        if (str[i] != '"' && str[i] != 39)
        {    
            ret[j] = str[i];
            j++;
        }
       i++;
    }
    if (env->check == 42)
        ret[j] = '\0';
    else
        ret[j] = '\n';
    ret[j + 1] = '\0';
    if (ret[0] == '\0' && env->check != 42)
        return ("\n");
    env->check = 42;
    return (ret);
}