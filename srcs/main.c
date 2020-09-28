/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/13 17:07:24 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	g_shell_env;

void		print_prompt(int return_to_line_before)
{
	char *str;
	char *i;

	str = NULL;
	str = getcwd(str, 1000000);
	if (return_to_line_before)
		ft_putstr_fd("\n", 2);
	if (g_shell_env.last_program_return)
		ft_putstr_fd(RED, 2);
	else
		ft_putstr_fd(GREEN, 2);
	ft_putstr_fd("[", 2);
	i = ft_itoa(g_shell_env.last_program_return);
	if (g_shell_env.last_program_return == 256)
		ft_putstr_fd("1", 2);
	else
		ft_putstr_fd(i, 2);
	ft_putstr_fd("] ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : "DEFAULT_COLOR, 2);
}

void		ft_sigint_cat(int value)
{
	(void)value;
	ft_putchar_fd('\n', 1);
	g_shell_env.last_program_return = 1;
}

void		ft_sigint(int value)
{
	(void)value;
	g_shell_env.last_program_return = 1;
	print_prompt(1);
}

int			main(int argc, char **argv, char **env)
{
	t_env_variable	env_variables;

	(void)argc;
	(void)argv;
	g_shell_env.data_env = env;
	g_shell_env.prog_name = argv[0];
	g_shell_env.last_program_return = 0;
	init_env_variables(&env_variables, &g_shell_env, env);
	move_init(&g_shell_env);
	print_prompt(0);
	start_get_commmand(&g_shell_env);
}
