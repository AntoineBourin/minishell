/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:49:10 by abourin           #+#    #+#             */
/*   Updated: 2020/02/05 14:45:01 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env_variables(t_env_variable *env_variables, t_env *env)
{
	env_variables->name = NULL;
	env_variables->content = NULL;
	env_variables->next = NULL;
	env->env_variables = env_variables;
}

int		main(int av, char **ac)
{
	t_env			env;
	t_env_variable	env_variables;
	(void)av;

	
	init_env_variables(&env_variables, &env);
	env.prog_name = ac[0];
	move_init(&env);									//init le dossier de depart a "/Users/"
	/*printf("%s\n", env.curr_path);					//equivaut au pwd
	move("/Users/nveron", 0, &env);						//equivaut au deplacement
	move(NULL, 1, &env);								//equivaut au pwd
	move("/Users/nveron/Desktop/minishell", 0, &env);	//equivaut au deplacement
	printf("\n%s\n", env.curr_path);					//le path est directement mis dans env.curr_path*/
	command_read(&env);
}
