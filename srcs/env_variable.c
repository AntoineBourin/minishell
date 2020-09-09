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

#include "minishell.h"

char	*execute_binary_file(char *path, char *args, t_env *env)
{
	int		error;
	pid_t	pid;
	char	**ac;

	pid = fork();
	ac = get_function_args(args);
	if (pid == 0)
	{
		error = execve(path, ac, env->data_env);
		error == -1 ? printf_error("Minishell", errno, path, NULL) : 0;
		ft_free(ac);
		return (NULL);
	}
	else
	{
		waitpid(pid, &(env->last_program_return), 0);
		return (NULL);
	}
	return (NULL);
}

int		is_command_path_to_file(char *path)
{
	struct stat		sb;
	int				res;

	res = stat(path, &sb);
	return (S_ISDIR(sb.st_mode) ? 2 : res);
}

int		get_nb_function_args(char *command)
{
	int		i;
	int		arg_count;

	i = 0;
	arg_count = 0;
	while (command[i])
	{
		if (command[i] == ' ')
			i++;
		else if (command[i] == '"')
		{
			arg_count++;
			i++;
			while (command[i] && command[i] != '"')
				i++;
		}
		else
		{
			arg_count++;
			while (command[i] && command[i] != ' ')
				i++;
		}
	}
	return (arg_count);
}


char	*fill_arg_value(char *arg_begin, int is_quoted)
{
	int		len;
	char	*arg;
	int		i;

	len = 0;
	while (arg_begin[len])
	{
		if (arg_begin[len] == '"' && is_quoted)
			break ;
		else if (arg_begin[len] == ' ' && !is_quoted)
			break ;
		len++;
	}
	if (!(arg = malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (arg_begin[i] && i < len)
	{
		arg[i] = arg_begin[i];
		i++;
	}
	arg[i] = '\0';
	return (arg);
}


int		exec_binary_norm(char ***t)
{
	if (!((*t) = malloc(sizeof(char *) * 2)))
		return (1);
	(*t)[0] = ft_strdup("TERM=xterm");
	(*t)[1] = NULL;
	return (0);
}

char	*get_function_args2(int *i, char *command, int *arg_i)
{
	int j;

	j = *i;
	(*arg_i)++;
	(*i)++;
	while (command[(*i)] && command[(*i)] != '"')
		(*i)++;
	while (command[(*i)] && command[(*i)] == '"')
		(*i)++;
	return (fill_arg_value(command + j + 1, 1));
}

int     check_if_char_is_in_str(char c, char *str)
{
    while (*str)
    {
        if (*str == c)
            return (1);
        str++;
    }
    return (0);
}

char    *cut_cmd_by_arg_fill(char *command, char **ac, char *str, int *arg_i)
{
    int i;

    i = 0;
    while (command[i] && check_if_char_is_in_str(command[i], str) != 1)
    {
        if (command[i] == 92)
            i++;
        i++;
    }
    if (!(ac[*arg_i] = malloc(sizeof(char) * i + 1)))
        return (NULL);
    i = 0;
    while (command[i] && check_if_char_is_in_str(command[i], str) != 1)
    {
        if (command[i] == 92)
            command++;
        ac[*arg_i][i] = command[i];
        i++;
    }
    ac[*arg_i][i] = '\0';
    (*arg_i)++;
    return (command + i);
}

char    *cut_cmd_by_arg_fill_2(char *command, char **ac, char *str, int *arg_i)
{
    int i;

    i = 0;
    while (command[i] && check_if_char_is_in_str(command[i], str) != 1)
        i++;
    if (!(ac[*arg_i] = malloc(sizeof(char) * i + 1)))
        return (NULL);
    i = 0;
    while (command[i] && check_if_char_is_in_str(command[i], str) != 1)
    {
        ac[*arg_i][i] = command[i];
        i++;
    }
    ac[*arg_i][i] = '\0';
    (*arg_i)++;
    if (command[i])
        return (command + i + 1);
    return (command + i);
}

void    cut_cmd_by_arg(char *command, char **ac)
{
    int i;
    int arg_i;

    i = 0;
    arg_i = 0;
    while (command[i])
    {
        if (command[i] == 34 || command[i] == 39)
        {
            if (command[i] == 34)
                command = cut_cmd_by_arg_fill_2(command + 1, ac, "\"", &arg_i);
            else if (command[i] == 39)
                command = cut_cmd_by_arg_fill_2(command + 1, ac, "'", &arg_i);
            i = 0;
        }
        else
        {
            while (*command == ' ')
                command++;
            if (command[i] && command[i] != 34 && command[i] != 39)
                command = cut_cmd_by_arg_fill(command, ac, "'\" ", &arg_i);
        }
    }
    ac[arg_i] = NULL;
}

char	**get_function_args(char *command)
{
	char	**ac;

    command = place_str_at_the_begin_command(command);
	if (!(ac = malloc(sizeof(char *) * (get_nb_function_args(command) + 3))))
		return (NULL);
	ac[get_nb_function_args(command)] = NULL;
    cut_cmd_by_arg(command, ac);
	return (ac);
}

void	ft_free(char **str)
{
	if (*str)
		free(*str);
	(*str) = NULL;
}


void	printf_error(char *name, int error, char *str, char *errorstr)
{
	ft_putstr_fd(name, 1);
	ft_putstr_fd(": ", 1);
	if (error != 0)
		ft_putstr_fd(strerror(error), 1);
	else
		ft_putstr_fd(errorstr, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
}

t_env_variable	*get_env_variable_if_exist(t_env_variable *env_variables,
							char *name)
{
	while (env_variables)
	{
		if (env_variables->name
			&& ft_strncmp(env_variables->name, name, ft_strlen(name)) == 0)
			return (env_variables);
		env_variables = env_variables->next;
	}
	return (NULL);
}

char	**get_env_full_path(char *path, t_env *env)
{
	t_env_variable	*path_env;
	int				len;
	char			*full_path;
	char			**paths;
	int				i;

	if (!(path_env = get_env_variable_if_exist(env->env_variables, "PATH")))
		return (NULL);
	i = 0;
	paths = ft_split(path_env->content, ':');
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		full_path = ft_strjoin(
			paths[i][len] != '/' ? ft_strjoin(paths[i], "/")
			: paths[i], path);
		free(paths[i]);
		paths[i] = full_path;
		i++;
	}
	return (paths);
}

int		command_path_to_file_with_env(char *path, t_env *env)
{
	char			**full_paths;
	int				i;

	i = 0;
	full_paths = get_env_full_path(path, env);
	while (full_paths && full_paths[i])
	{
		if (is_command_path_to_file(full_paths[i]) == 0)
		{
			free(full_paths);
			return (0);
		}
		free(full_paths[i]);
		i++;
	}
	free(full_paths);
	return (-1);
}

int		get_env_list_size(t_env_variable *variables)
{
	int		nb;

	nb = 0;
	while (variables)
	{
		nb++;
		variables = variables->next;
	}
	return (nb);
}

char	*execute_env_binary_file2(t_env *env, char **t, char *path, int i)
{
	int error;

	error = execve(env->full_paths[i], env->ac, t);
   
	error == -1 ? printf_error("Minishell", errno, path, NULL) : 0;
	return (NULL);
}

char	*execute_env_binary_file(char *binary, char *path, t_env *env)
{
	int				i;
	char			**t;
	pid_t			pid;

	if (exec_binary_norm(&t))
		return (NULL);
	i = 0;
	env->full_paths = get_env_full_path(binary, env);
	while (env->full_paths[i])
	{
		if (is_command_path_to_file(env->full_paths[i]) == 0)
		{
			pid = fork();
			if (pid == 0)
				return (execute_env_binary_file2(env, t, path, i));
			else
				waitpid(pid, &(env->last_program_return), 0);
			ft_free(t);
			return (NULL);
		}
		i++;
	}
	ft_free(t);
	return (NULL);
}

void	move_init(t_env *env)
{
	int				check_error;
	char			*buff;
	t_env_variable	*home;

	home = get_env_variable_if_exist(env->env_variables, "HOME");
	if (home && home->content)
		check_error = chdir(home->content);
	else
		check_error = chdir("/Users");
	buff = NULL;
	buff = getcwd(buff, 1000000);
	if (!(env->curr_path = malloc(sizeof(char) * ft_strlen(buff))))
		return ;
	env->curr_path = buff;
}


char	*get_arg_quotes(char *arg, char charset)
{
	int		is_quoted;
	int		i;

	i = 0;
	if (arg && arg[0] && arg[0] == '"')
		is_quoted = 1;
	if (arg && arg[0] && arg[0] == '"')
		i++;
	else
		is_quoted = 0;
	while (arg && arg[i])
	{
		if ((arg[i] == charset) || (arg[i] == ' ' && !is_quoted))
		{
			arg[i] = '\0';
			return (arg);
		}
		if (arg[i] == '"' && is_quoted)
		{
			arg[i] = '\0';
			return (arg + 1);
		}
		i++;
	}
	return (arg);
}

void			push_env_variable_list(t_env_variable *env_variables,
						char *name, char *value)
{
	t_env_variable	*tmp;
	t_env_variable	*new;

	if ((tmp = get_env_variable_if_exist(env_variables, name)) != NULL)
	{
		tmp->content = value;
		return ;
	}
	if (!(new = malloc(sizeof(t_env_variable))))
		return ;
	tmp = env_variables;
	while (tmp)
	{
		if (!tmp->next)
		{
			tmp->next = new;
			new->name = name;
			new->content = value;
			new->next = NULL;
			return ;
		}
		tmp = tmp->next;
	}
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