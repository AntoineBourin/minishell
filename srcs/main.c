/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:49:10 by abourin           #+#    #+#             */
/*   Updated: 2020/01/31 15:00:12 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int av, char **ac)
{
	t_env		env;
	(void)av;
	(void)ac;

	move_init(&env);									//init le dossier de depart a "/Users/"
	/*printf("%s\n", env.curr_path);						//equivaut au pwd
	move("/Users/nveron", 0, &env);						//equivaut au deplacement
	move(NULL, 1, &env);								//equivaut au pwd
	move("/Users/nveron/Desktop/minishell", 0, &env);	//equivaut au deplacement
	printf("\n%s\n", env.curr_path);					//le path est directement mis dans env.curr_path*/
	command_read(&env);
}
