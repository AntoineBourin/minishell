/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:54:05 by abourin           #+#    #+#             */
/*   Updated: 2020/02/04 13:36:47 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>  
# include "libft.h"

typedef struct			s_environment
{
	char				**command;
	char				*curr_path;
}						t_env;

void		command_read(t_env *env);
void    	move_init(t_env *env);
void		move(char *str, int pwd, t_env *env);
void		cd_split(t_env *env, char *buff);
void		command_middleware(t_env *env, char *input);
#endif
