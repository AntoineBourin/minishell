/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:49:10 by abourin           #+#    #+#             */
/*   Updated: 2020/02/12 11:09:50 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	g_shell_env;

void	ft_exit(int i)
{
	char *str;

	(void)i;
	str = NULL;
	str = getcwd(str, 1000000);
	g_shell_env.last_program_return = 1;
	write(1, "\n", 1);
	if (g_shell_env.last_program_return)
		ft_putstr_fd("\033[1;31m", 1);
	else
		ft_putstr_fd("\033[1;32m", 1);
	write(1, "[", 1);
	ft_putstr_fd(ft_itoa(g_shell_env.last_program_return), 1);
	write(1, "] ", 2);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(" : ", 1);
	ft_putstr_fd("\033[0;m", 1);
}

void	init_env_variables(t_env_variable *env_variables, t_env *shell_env,
					char **env)
{
	int		i;
	int		j;

	env_variables->name = "PATH";
	env_variables->content = "/Users";
	env_variables->next = NULL;
	shell_env->env_variables = env_variables;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		push_env_variable_list(env_variables, get_arg_quotes(env[i], '='),
						get_arg_quotes(env[i] + j + 1, 0));
		i++;
	}
}

int		main(int av, char **ac, char **env)
{
	t_env_variable	env_variables;

	(void)av;
	g_shell_env.data_env = env;
	g_shell_env.last_program_return = 0;
	init_env_variables(&env_variables, &g_shell_env, env);
	g_shell_env.prog_name = ac[0];
	move_init(&g_shell_env);
	command_read(&g_shell_env);
}
