/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:54:05 by abourin           #+#    #+#             */
/*   Updated: 2020/02/26 11:46:11 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>  
# include "libft.h"

typedef struct				s_env_variable
{
	char					*name;
	char					*content;
	struct s_env_variable	*next;
}							t_env_variable;

typedef struct			s_environment
{
	int					check;
	char				**full_paths;
	int					error;
	char				**ac;
	int					ope_type;
	char				**command;
	char				*curr_path;
	char				*prog_name;
	char				**data_env;
	int					last_program_return;
	t_env_variable		*env_variables;
}						t_env;

typedef struct	s_comp
{
	size_t compt;
	int start;
	int end;
	int exp_1;
	int exp_2;
}				t_comp;

typedef struct	s_quote
{
	int i;
	int j;
	int check34;
	int check39;
	char *copy;
}				t_quote;

char 			*get_function_args2(int *i, char *command, int *arg_i);
char    		*red_name(char *str);
void			ft_red(t_list *commands, t_env *env, char *str);
char			*execute_env_binary_fie2(t_env *env, char **t, char *path, int i);
int				ft_check_red(char *str, char *sep);
int 			ft_check_red_char(char c, char *str);
void			command_read(t_env *env);
void    		move_init(t_env *env);
void			move(char *str, int pwd, t_env *env);
void			cd_split(t_env *env, char *buff);
void			command_middleware(t_env *env, char *input);
void    		printf_error(char *name, int error, char *str, char *errorstr);
char			*pwd(t_env *env, char *args);
void			display_commands_result(t_list *commands);
int				is_command_path_to_file(char *path);
char			*execute_binary_file(char *path, char *args, t_env *env);
char 			*export_env(t_env *env, char *cmd, char *args);
char			*get_arg_quotes(char *arg, char charset);
char			*display_env_list(t_env *env);
char    		*echo_main(t_env *env, char *str);
int     		check_arg_n(char *str);
t_env_variable	*get_env_variable_if_exist(t_env_variable *env_variables,
								char *name);
void			remove_env_variable(t_env_variable **env_variables, char *name);
void			unset(t_env *env, char *cmd, char *args);
char			*env_translator(char *user_input, t_env *env);
int				command_path_to_file_with_env(char *path, t_env *env);
char			*execute_env_binary_file(char *binary, char *path, t_env *env);
void			push_env_variable_list(t_env_variable *env_v, char *name, char *value);
char			**get_function_args(char *commannd);
void			replace_env_name_by_value(char **res, t_env_variable *env,
									int begin_index, int end_index);
char			**ft_split_modif(char const *s, char c);
int				execute_pipes_command(t_list *commands, t_env *env,
							char *command, char *piped);
char			*red_cut(t_list *commands, t_env *env, char *str);
char			*remove_quote_arg(char *str);
#endif
