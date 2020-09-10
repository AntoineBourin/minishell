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

int     check_if_quote(char *str, int j)
{
	int i;
	int presence_of_34;
	int presence_of_39;

	presence_of_34 = -1;
	presence_of_39 = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 && presence_of_39 < 0)
        {
			presence_of_34 *= -1;
            if (i == j)
                return (2);
        }
		if (str[i] == 39 && presence_of_34 < 0)
        {
			presence_of_39 *= -1;
            if (i == j)
                return (2);
        }
		if (presence_of_39 < 0 && presence_of_34 < 0)
		{
			if (str[i] == 92 && str[i + 1] != '\0')
				i++;
		}
        else
        {
            if (i == j)
                return (1);
        }
		i++;
	}
	return (0);
}

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
    int j;

    i = 0;
    j = 1;
    if (ac[j] != '\0' && ft_strncmp(ac[j], "-n", 3) == 0)
    {
        while (ac[j] != '\0' && ft_strncmp(ac[j], "-n", 3) == 0)
        {
            while (str[i] != '-')
                i++;
            i += 2;
            j++;
        }
    }
    else
        i += 4;
    while (str[i] == ' ')
        i++;
    while (str[i])
    {
        if (check_if_quote(str, i) == 1)
        {
            ft_putchar_fd(str[i], 1);
        }
        else if (check_if_quote(str, i) == 0 && check_if_is_the_end_of_the_cmd(str, i) == 0)
            ft_putchar_fd(str[i], 1);
        i++;
    }
    if (ft_strncmp(ac[1], "-n", 3) != 0)
        ft_putchar_fd('\n', 1);
    env->last_program_return = 0;
}