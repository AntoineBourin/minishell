/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/04 11:01:47 by nveron           ###   ########.fr       */
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

typedef struct				s_quote
{
	int						i;
	int						j;
	int						check34;
	int						check39;
	char					*copy;
}							t_quote;

typedef struct				s_comp
{
	size_t					compt;
	int						start;
	int						end;
	int						exp_1;
	int						exp_2;
	int						exp_3;
	size_t					i;
	size_t					j;
	size_t					k;
	char					*res;
	char					*cop;
	size_t					size;
}							t_comp;

void            init_env_variables(t_env_variable *env_variables, t_env *shell_env, char **env);
void            print_prompt(int return_to_line_before);
void	        printf_error(char *name, int error, char *str, char *errorstr);
t_env_variable	*get_env_variable_if_exist(t_env_variable *env_variables,char *name);
char	        **get_env_full_path(char *path, t_env *env);
int		        command_path_to_file_with_env(char *path, t_env *env);
int		        get_env_list_size(t_env_variable *variables);
char	        *execute_env_binary_file2(t_env *env, char **t, char *path, int i);
char	        *execute_env_binary_file(char *binary, char *path, t_env *env);
void	        move_init(t_env *env);
char	        *get_arg_quotes(char *arg, char charset);
void	        push_env_variable_list(t_env_variable *env_variables,char *name, char *value);
void	        init_env_variables(t_env_variable *env_variables, t_env *shell_env,char **env);
char	        **get_function_args(char *command);
char	        *get_function_args2(int *i, char *command, int *arg_i);
int		        exec_binary_norm(char ***t);
char	*fill_arg_value(char *arg_begin, int is_quoted);
int		get_nb_function_args(char *command);
int		is_command_path_to_file(char *path);
char    *get_name_command_fonction_without_quote(char *str);
char    *command_name_with_or_without_quote(char *str);
char    *get_name_command_fonction_with_quote(char *str, char quote);
void		ft_sigint_cat(int value);
void		ft_sigint(int value);
void    command_read(char *buff, t_env *env);
int     check_if_quote_are_close(char *str);
void    start_get_commmand(t_env *env);
char *place_str_at_the_begin_command(char *str);
void	ft_free(char **str);
void	pwd(t_env *env, char *args);
void		cd_split(t_env *env);
void	replace_env_name_by_value(char **res, t_env_variable *env,int begin_index, int end_index);
void		unset(t_env *env, char *cmd, char *args);
char 	*display_env_list(t_env *env);
char			*export_env(t_env *env, char *cmd, char *args);
char	*remove_quote_arg(char *str);
void    echo_main(char *str, char **ac, t_env *env);
char	*env_translator(char *user_input, t_env *env);
void    ft_exit(t_env *env);
char	*execute_binary_file(char *path, char *args, t_env *env);
int		execute_pipes_command(t_list *commands, t_env *env, char *command, char *piped);
int		execute_pipe_norm10(char **copy, t_env *env);
void	execute_pipe_norm9(t_env *env, int *fd_red, char *piped, char *copy);
void	execute_pipe_norm8(int *fd_red, char *piped, int i);
int		execute_pipe_norm3(char *piped, char *copy, int *j, int *i);
void	execute_pipe_norm2(char *piped, int *i, int *j, char *copy);
void	execute_pipe_norm1(char **copy, char *command, t_env *env, int *fd_red);
int		run_pipe(t_list *commands, t_env *env, char *str, int *fd);
void	run_pipe2(t_env *env, int *fd);
void	execute_pipe_norm7(int fd_red, t_env *env, char *piped, int i);
int		execute_pipe_norm6(int fd_red, char **copy);
void	execute_pipe_norm5(t_env *env, int *fd_red, int *i, char *piped);
int		execute_pipe_norm4(t_env *env, char **copy, int *fd, t_list *commands);
void	ft_strcpy_s(const char *src, const char *src2, char *dest);
void	ft_red(t_list *commands, t_env *env, char *str);
void	ft_red_norm7(char *str, t_comp *c1, t_list *commands, t_env *env);
void	ft_red_norm6(t_comp *c1, t_list *commands, t_env *env, char *str);
void	ft_red_norm5(char **copy, t_comp *c1, char *str);
int		ft_red_norm4(t_comp *c1, char *str, char **copy, t_env *env);
void	ft_red_norm3(t_comp *c1, t_list *commands, t_env *env, char *str);
void	ft_red_norm2(char *str, t_comp *c1, t_list *commands, t_env *env);
void	ft_red_norm1(char *str, t_comp *c1, t_list *commands, t_env *env);
int				ft_check_red_char(char c, char *str);
int		check_before(char *str, int i, char c);
char	*check_exeption_chiante(char *ref, char *str, char *name);
char	*red_name(char *str);
char	*sort_with_red(t_list *commands, t_env *env,
		char *first, char *second);
char	*sort_with_red_norm1(t_list *commands, t_env *env, char **copy, char *first);
char						*red_cut(t_list *commands, t_env *env, char *str);
int							ft_check_red(char *str, char *sep);
int							ft_check_red_char(char c, char *str);
int				ft_norm_check_red(t_comp *all, char *str);

#endif

#ifndef BG_LIGHT

#define BLACK    "\033[1;30m"
#define RED      "\033[1;31m"
#define GREEN    "\033[1;32m"
#define YELLOW   "\033[1;33m"
#define BLUE     "\033[1;34m"
#define PURPLE   "\033[1;35m"
#define CYAN     "\033[1;36m"
#define GREY     "\033[1;37m"

#else // else BG_LIGHT

#define BLACK    "\033[0;30m"
#define RED      "\033[0;31m"
#define GREEN    "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define BLUE     "\033[0;34m"
#define PURPLE   "\033[0;35m"
#define CYAN     "\033[0;36m"
#define GREY     "\033[0;37m"

#endif // endif BG_LIGHT

#define DEFAULT_COLOR "\033[0;m"