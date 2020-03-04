/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:54:05 by abourin           #+#    #+#             */
/*   Updated: 2020/03/04 07:53:14 by nveron           ###   ########.fr       */
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

typedef struct				s_environment
{
	int					i;
	int					j;
	int					check;
	int					check_sign;
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

}							t_env;

typedef struct				s_comp
{
	size_t					compt;
	int						start;
	int						end;
	int						exp_1;
	int						exp_2;
	size_t					i;
	size_t					j;
	size_t					k;
	char					*res;
	char					*cop;
}							t_comp;

typedef struct				s_quote
{
	int						i;
	int						j;
	int						check34;
	int						check39;
	char					*copy;
}							t_quote;

int							execute_pipe_norm3(char *piped, char *copy, int *j,
							int *i);
void						ft_free(char **str);
void						execute_pipe_norm2(char *piped, int *i, int *j,
							char *copy);
void						execute_pipe_norm1(char **copy, char *command, t_env
							*env, int *fd_red);
int							run_pipe(t_list *commands, t_env *env, char *str,
							int *fd);
void						run_pipe2(t_env *env, int *fd);
void						execute_pipe_norm8(int *fd_red, char *piped, int i);
void						execute_pipe_norm9(t_env *env, int *fd_red,
							char *piped, char *copy);
void						ft_strcpy_s(const char *src, const char *src2,
							char *dest);
void						execute_pipe_norm7(int fd_red, t_env *env,
							char *piped, int i);
int							execute_pipe_norm6(int fd_red, char **copy);
void						execute_pipe_norm5(t_env *env, int *fd_red, int *i,
							char *piped);
int							execute_pipe_norm4(t_env *env, char **copy, int *fd,
							t_list *commands);
int							ft_split_modif_norm1(t_comp *c1, const char *s,
							int i, char c);
void						ft_sort(t_env *env, t_list *command);
void						ft_split_modif_norm2(t_comp *c1, char ***new,
							size_t *j, size_t *i);
void						replace_env_norm1(char ***res, t_comp *c1,
							int begin_index, char **tmp);
void						replace_env_norm2(int *length, t_env_variable *env);
char						*ft_army_if_red_norm1(t_env *env, char *cop,
							char *str, t_list *command);
char						*check_exeption_chiante(char *ref, char *str,
							char *name);
int							check_before(char *str, int i, char c);
char						*sort_with_red(t_list *commands, t_env *env,
							char *first, char *second);
char						*red_name(char *str);
void						ft_red_norm1(char *str, t_comp *c1,
							t_list *commands, t_env *env);
void						ft_red_norm2(char *str, t_comp *c1,
							t_list *commands, t_env *env);
void						ft_red_norm3(t_comp *c1,
							t_list *commands, t_env *env, char *str);
int							ft_red_norm4(t_comp *c1, char *str,
							char **copy, t_env *env);
char						*get_function_args2(int *i, char *command,
							int *arg_i);
char						*red_name(char *str);
void						ft_red(t_list *commands, t_env *env, char *str);
char						*execute_env_binary_fie2(t_env *env, char **t,
							char *path, int i);
int							ft_check_red(char *str, char *sep);
int							ft_check_red_char(char c, char *str);
void						command_read(t_env *env);
void						move_init(t_env *env);
void						move(char *str, int pwd, t_env *env);
void						cd_split(t_env *env, char *buff);
void						command_middleware(t_env *env, char *input);
void						printf_error(char *name, int error, char *str,
							char *errorstr);
char						*pwd(t_env *env, char *args);
void						display_commands_result(t_list *commands);
int							is_command_path_to_file(char *path);
char						*execute_binary_file(char *path,
							char *args,
							t_env *env);
char						*export_env(t_env *env, char *cmd, char *args);
char						*get_arg_quotes(char *arg, char charset);
char						*display_env_list(t_env *env);
char						*echo_main(t_env *env, char *str);
int							check_arg_n(char *str);
t_env_variable				*get_env_variable_if_exist(t_env_variable
							*env_variables, char *name);
void						remove_env_variable(t_env_variable
							**env_variables, char *name);
void						unset(t_env *env, char *cmd, char *args);
char						*env_translator(char *user_input, t_env *env);
int							command_path_to_file_with_env(char *path,
							t_env *env);
char						*execute_env_binary_file(char *binary,
							char *path, t_env *env);
void						push_env_variable_list(t_env_variable *env_v,
							char *name, char *value);
char						**get_function_args(char *commannd);
void						replace_env_name_by_value(char **res,
				t_env_variable *env, int begin_index, int end_index);
char						**ft_split_modif(char const *s, char c);
int							execute_pipes_command(t_list *commands, t_env *env,
							char *command, char *piped);
char						*red_cut(t_list *commands, t_env *env, char *str);
char						*remove_quote_arg(char *str);
#endif
