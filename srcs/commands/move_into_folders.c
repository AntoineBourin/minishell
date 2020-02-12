/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_into_folder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:06:25 by nveron            #+#    #+#             */
/*   Updated: 2020/02/12 11:37:15 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    move_init(t_env *env)
{
    int				check_error;
	char			*buff;
	t_env_variable	*home;

	home = get_env_variable_if_exist(env->env_variables, "HOME");
	if (home && home->content)
		check_error = chdir(home->content);
	else
		check_error = chdir("/Users");
	buff = NULL;
    buff = getcwd(buff, 1000000);

    if (!(env->curr_path = malloc(sizeof(char) * ft_strlen(buff))))
	    return ;
    env->curr_path = buff;
}

void    printf_error(char *name, int error, char *str, char *errorstr)
{
    ft_putstr_fd(name, 1);
    ft_putstr_fd(": ", 1);
    if (error != 0)
        ft_putstr_fd(strerror(error), 1);
    else
        ft_putstr_fd(errorstr, 1);
    ft_putstr_fd(": ", 1);
    ft_putstr_fd(str, 1);
    ft_putchar_fd('\n', 1);
}

void	replace_tild_by_home(char **str, t_env *env)
{
	t_env_variable	*home;
	int				i;

	i = 0;
	if (!(home = get_env_variable_if_exist(env->env_variables, "HOME")))
		return ;
	home->name = "~";
	while ((*str)[i])
	{
		if ((*str)[i] == '~')
			replace_env_name_by_value(str, home, i, i);
		i++;
	}
	home->name = "HOME";
}

void    move(char *str, int pwd, t_env *env)
{
	int		check_error;
	char	*buff;
    int		i;

    i = 0;
	buff = NULL;
    if (str == NULL && pwd == 0)
    {
        move_init(env);
        return ;
    }
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\v' || *str == '\f' )
		str++;
	replace_tild_by_home(&str, env);
    buff = getcwd(buff, 1000000);
    if (pwd != 0 && str == NULL)
	    ft_putstr_fd(buff, 1);
    else if (pwd == 0 && str != NULL)
    {
	    check_error = chdir(str);
        buff = getcwd(buff, 1000000);
        if (check_error != 0)
            printf_error("cd", ENOENT, str, NULL);
        free(env->curr_path);
        env->curr_path = NULL;
        if (!(env->curr_path = malloc(sizeof(char) * ft_strlen(buff))))
		    return ;
        env->curr_path = buff;
    }
}
