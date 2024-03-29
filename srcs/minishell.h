/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/10/04 22:17:10 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define DEFAULT_COLOR	"\033[0;m"
# define BLACK			"\033[1;30m"
# define RED			"\033[1;31m"
# define GREEN			"\033[1;32m"
# define YELLOW			"\033[1;33m"
# define BLUE			"\033[1;34m"
# define PURPLE			"\033[1;35m"
# define CYAN			"\033[1;36m"
# define GREY			"\033[1;37m"

# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct				s_errlist
{
	char					*name;
	struct s_errlist		*next;
}							t_errlist;

typedef struct				s_fdlist
{
	int						fd;
	struct s_fdlist			*next;
}							t_fdlist;

typedef struct				s_cmdlist
{
	void					*command;
	t_fdlist				*fd_in;
	t_fdlist				*fd_out;
	t_fdlist				*fd_out_err;
	t_errlist				*error;
	int						check_error;
	struct s_cmdlist		*next;
}							t_cmdlist;

typedef struct				s_env_variable
{
	char					*name;
	char					*content;
	struct s_env_variable	*next;
}							t_env_variable;

typedef struct				s_environment
{
	int						l;
	int						i;
	int						j;
	int						presence_of_34;
	int						presence_of_39;
	int						check_fd_in;
	int						check_fd_out;
	int						check;
	int						check_sign;
	char					**full_paths;
	int						error;
	char					**ac;
	int						nbr_redir;
	int						ope_type;
	char					**command;
	char					*curr_path;
	char					*prog_name;
	char					**data_env;
	int						last_program_return;
	t_env_variable			*env_variables;
	t_env_variable			*env_declare;
	t_cmdlist				cmdlist;
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

t_env	g_shell_env;

void						init_env_variables(t_env_variable
*env_variables, t_env *shell_env, char **env);
void						print_prompt(int return_to_line_before);
void						printf_error(char
*name, int error, char *str, char *errorstr);
t_env_variable				*get_env_variable_if_exist(t_env_variable
*env_variables, char *name);
char						**get_env_full_path(char *path, t_env *env);
int							command_path_to_file_with_env(char *path,
t_env *env);
int							get_env_list_size(t_env_variable *variables);
char						*execute_env_binary_file2(t_env *env,
char **t, char *path, int i);
char						*execute_env_binary_file(char *binary,
char *path, t_env *env);
void						move_init(t_env *env);
char						*get_arg_quotes(char *arg, char charset);
void						push_env_variable_list(t_env_variable
*env_variables, char *name, char *value);
void						init_env_variables(t_env_variable
*env_variables, t_env *shell_env, char **env);
char						**get_function_args(char *command);
char						*get_function_args2(int *i, char *command,
int *arg_i);
char						**exec_binary_norm(char **t);
char						*fill_arg_value(char *arg_begin, int is_quoted);
int							get_nb_function_args(char *command);
int							is_command_path_to_file(char *path);
char						*get_name_command_fonction_without_quote(char *str);
char						*command_name_with_or_without_quote(char *str);
char						*get_name_command_fonction_with_quote(char *str,
char quote);
void						ft_sigint_cat(int value);
void						ft_sigint(int value);
void						command_read(char *buff, t_env *env);
int							check_if_quote_are_close(char *str);
void						start_get_commmand(t_env *env);
char						*place_str_at_the_begin_command(char *str);
void						ft_free(char **str);
void						pwd(t_env *env, char *args);
void						cd_split(t_env *env);
void						replace_env_name_by_value(char **res,
t_env_variable *env, int begin_index, int end_index);
void						unset(t_env *env, char *cmd, char *args);
char						*display_env_list(t_env *env);
char						*export_env(t_env *env, char *args);
char						*remove_quote_arg(char *str);
void						echo_main(char *str, char **ac, t_env *env);
char						*env_translator(char *user_input, t_env *env);
void						ft_exit(t_env *env);
char						*execute_binary_file(char *path, char *args,
t_env *env);
int							check_if_char_in_str_is_in_str2(char *charset,
char *str);
void						redirection_sort(char *str, t_env *env);
int							check_if_char_is_in_str(char c, char *str);
int							check_if_char_is_in_str_modif(char *str,
char *charset, int x);
int							check_if_char_in_str_is_in_str2_modif(
char *charset, char *str);
int							check_if_quote_norm3(char *str, int *i,
int j, t_env *env);
void						command_remove_quote_etc_norm1(char **str,
char *ref_str, int *presence_of_34, int *presence_of_39);
void						command_remove_quote_etc_norm2(char **str,
char **buff);
int							check_norm_1(char *str,
int *i, int *j, char *charset);
char						**split_modif(char *str);
void						execute_and_sort_cmd(char *str, t_env *env);
void						exec_cmd_redirection_list(t_fdlist *lst,
			t_cmdlist *list_2, t_env *env);
int							cut_cmd_for_pipe_and_redirection_malloc(
	char ***ac, char *str);
void						fdlist_print(t_fdlist *lst);
void						fdlist_clear(t_fdlist **lst);
void						fdlist_add_back(t_fdlist **alst,
t_fdlist *new);
int							cut_cmd_for_pipe_and_redirection_norme1(
char *str, char **ac, int j, int x);
void						pipe_select_norm2(t_env *env, char *str,
int fd_out);
void						pipe_select_norm1(t_env *env, char *str,
int fd_out);
t_cmdlist					*fill_list(t_env *env, char **ac, char *str);
void						exec_cmd_redirection(t_cmdlist **list,
t_env *env);
t_fdlist					*fdlist_new(int fd);
t_cmdlist					*cmdlist_new(void *command);
char						**cut_cmd_for_pipe_and_redirection(char **str);
void						ft_free_ac(char **ac);
void						redirection(char *str,
int fd_in, int fd_out, t_env *env);
void						exec_cmd_with_fd_in(char **last_cmd,
t_fdlist *list, int fd_out, t_env *env);
int							check_error_open(t_cmdlist *list, char *cmd);
void						cmdlist_print(t_cmdlist *lst);
int							cut_cmd_for_pipe_and_redirection_malloc_2(
	char ***ac, char *str);
int							cut_cmd_for_pipe_and_redirection_norme1_2(
	char *str, char **ac, int j, int x);
int							cut_cmd_norm1(char *str, char **ac, int x);
char						**cut_cmd_for_pipe_and_redirection_2(
	char **str);
int							echo_main_norm_4(char *str, int i);
char						*env_and_export(char *str, t_env *env);
int							ft_content_exist(t_env *env, char *str);
char						*ft_print_env(t_env *env);
void						ft_print_declare_env(t_env *env);
t_env_variable				*f_lstlast(t_env_variable *lst);
void						exec_cmd_redirection_for_pipe(t_env
*env, char *ref);
void						cut_cmd_for_pipe(char **str, char **ref);
int							check_str_char_in_quote(char *c, char *str);
void						ft_pipe(char *str, t_env
*env, int *fd, int check);

char						**in_order(char **tab);
char						**list_to_tab(t_env_variable *env);
int							ft_size(t_env_variable *lst);
void						ft_free_tab(char **tab);
t_env_variable				*order(t_env_variable *list);

int							ft_search(char *s, char c);
int							ft_error_semi(char *s, t_env *env);
int							call_error(int redir, int back, t_env *env);
int							error_redir_2(char *s, t_env *env);
int							error_redir(char *s, t_env *env);

int							ft_error(char *s, t_env *env);
void						error_2(char *s, int i);

int							len_back(char *str);
char						*escape_backslash(char *str, t_env *env);
int							is_redir(int redir, int back);
int							check_redir(char *s);
int							search_pipe(char *s, char c);
void						free_tab(char **t, char **full_paths);

int							again(char *s);
int							again_2(char *s);
int							again_3(char *s);
int							help_search(char *s, int i);
int							help_redir(int redir, int back);
void						error_semi_norm(t_env *env);
int							help_error(char *s, t_env *env);
void						help_translator(char *s, int i, t_env *env);
int							len_tab(char **tab);
char						*fill_path(char **paths, int i, char *cmd);

void						more_ex(t_env *env, char *env_name, char *env_group,
							char *env_value);
int							verif_export_var(char *cmd, t_env *env, char *tot);
int							var_exist(t_env_variable *list, char *var);
char						*content_exist(t_env_variable *list, char *var);
void						push_value(t_env *env, char *env_value,
							char *env_group, char *env_name);
void						add_back(t_env_variable **alst,
							t_env_variable *new);
void						command_read_norm_free(t_env *env, char **str);
#endif
