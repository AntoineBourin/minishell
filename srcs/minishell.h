/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:54:05 by abourin           #+#    #+#             */
/*   Updated: 2020/02/05 14:15:57 by abourin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>  
# include "libft.h"

typedef struct			s_environment
{
	char				**command;
	char				*curr_path;
	char				*prog_name;
}						t_env;

void		command_read(t_env *env);
void    	move_init(t_env *env);
void		move(char *str, int pwd, t_env *env);
void		cd_split(t_env *env, char *buff);
void		command_middleware(t_env *env, char *input);
void    	printf_error(char *name, int error, char *str, char *errorstr);
char		*pwd(t_env *env, char *args);
void		display_commands_result(t_list *commands);
int			is_command_path_to_file(char *path);
char		*execute_binary_file(char *path, char *args);
#endif
