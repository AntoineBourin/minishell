/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/10 16:42:24 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		replace_tild_by_home(char **str, t_env *env)
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

void		move_norm(int check_error, char *str, t_env *env)
{
	if (check_error != 0)
	{
		printf_error("cd", ENOENT, str, NULL);
		env->last_program_return = 1;
	}
	else
		env->last_program_return = 0;
}

void		move(char *str, t_env *env)
{
	int		check_error;
	char	*buff;
	int		i;

	i = 0;
	buff = NULL;
	if (str == NULL)
	{
		move_init(env);
		return ;
	}
	replace_tild_by_home(&str, env);
	buff = getcwd(buff, 1000000);
	check_error = chdir(str);
	buff = getcwd(buff, 1000000);
	move_norm(check_error, str, env);
	free(env->curr_path);
	env->curr_path = NULL;
	if (!(env->curr_path = malloc(sizeof(char) * ft_strlen(buff))))
		return ;
	env->curr_path = buff;
}

void		cd_split(t_env *env)
{
	if (env->ac[1] != '\0' && env->ac[2] != '\0')
	{
		ft_putstr_fd("cd: string not in pwd: ", 1);
		ft_putstr_fd(env->ac[1], 1);
		ft_putchar_fd('\n', 1);
		env->last_program_return = 1;
	}
	else
	{
		if (env->ac[1] == '\0')
			move(NULL, env);
		else
			move(env->ac[1], env);
	}
}
