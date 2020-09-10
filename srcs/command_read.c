/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/10 16:44:47 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     number_of_split(char *str)
{
	int presence_of_34;
	int presence_of_39;
	int nbr_split;

	nbr_split = 1;
	presence_of_34 = -1;
	presence_of_39 = -1;
	while (*str)
	{
		if (*str == 34 && presence_of_39 < 0)
			presence_of_34 *= -1;
		if (*str == 39 && presence_of_34 < 0)
			presence_of_39 *= -1;
		if (presence_of_39 < 0 && presence_of_34 < 0)
		{
			if (*str == 92 && *(str + 1) != '\0')
				str += 1;
			else if (*str == ';')
				nbr_split++;
		}
		str++;
	}
	return (nbr_split);
}

int     is_a_separator(char *str, int j)
{
	int presence_of_34;
	int presence_of_39;
	int i;

	i = 0;
	presence_of_34 = -1;
	presence_of_39 = -1;
	while (str[i])
	{
		if (str[i] == 34 && presence_of_39 < 0)
			presence_of_34 *= -1;
		if (str[i] == 39 && presence_of_34 < 0)
			presence_of_39 *= -1;
		if (presence_of_39 < 0 && presence_of_34 < 0)
		{
			if (str[i] == 92 && str[i + 1] != '\0')
				i++;
			else if (str[i] == ';' && i == j)
				return (1);
		}
		i++;
	}
	return (0);
}

char **split_modif(char *str)
{
	char **cmd;
	int j;
	int i;

	i = 0;
	j = 0;
	if (!(cmd = malloc(sizeof(char*) * (number_of_split(str) + 1))))
		return (NULL);
	while (str[i])
	{
		while (str[i] && is_a_separator(str, i) != 1)
			i++;
		if (!(cmd[j] = malloc(sizeof(char) * (i + 1))))
			return (NULL);
		i = 0;
		while (*str && *str == ' ')
			str++;
		while (str[i] && is_a_separator(str, i) != 1)
		{
			cmd[j][i] = str[i];
			i++;
		}
		cmd[j][i] = '\0';
		j++;
		str += i;
		if (*str == ';')
			str++;
		i = 0;
	}
	cmd[j] = NULL;
	return (cmd);
}

int     check_if_char_in_str_is_in_str2_modif(char *charset, char *str)
{
	int i;
	int j;
	int presence_of_34;
	int presence_of_39;

	presence_of_34 = -1;
	presence_of_39 = -1;
	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == 34 && presence_of_39 < 0)
			presence_of_34 *= -1;
		if (str[i] == 39 && presence_of_34 < 0)
			presence_of_39 *= -1;
		if (presence_of_39 < 0 && presence_of_34 < 0)
		{
			if (str[i] == 92 && str[i + 1] != '\0')
				i++;
			else
				while (charset[j])
				{
					if (charset[j] == str[i])
						return (1);
					j++;
				}
		}
		i++;
	}
	return (0);
}

int     check_if_char_is_in_str_modif(char c, char *str, char *charset, int x)
{
	int i;
	int j;
	int presence_of_34;
	int presence_of_39;

	presence_of_34 = -1;
	presence_of_39 = -1;
	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == 34 && presence_of_39 < 0)
			presence_of_34 *= -1;
		if (str[i] == 39 && presence_of_34 < 0)
			presence_of_39 *= -1;
		if (presence_of_39 < 0 && presence_of_34 < 0)
		{
			if (str[i] == 92 && str[i + 1] != '\0')
				i++;
			else
				while (charset[j])
				{
					if (charset[j] == str[i] && i == x)
						return (1);
					j++;
				}
		}
		i++;
	}
	return (0);
}

void    execute_and_sort_cmd(char *str, t_env *env)
{
	if (check_if_char_in_str_is_in_str2_modif("<>|", str))
		redirection_sort(str, env);
	else
		command_read(str, env);
}

void    start_read_command(char *buff, t_env *env)
{
	char **cmd;
	int i;

	i = 0;
	cmd = split_modif(buff);
	env->last_program_return = 0;
	while (cmd[i])
	{
		execute_and_sort_cmd(cmd[i], env);
		i++;
	}
}

void		ft_signal(int i)
{
	if (i)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, ft_sigint);
	}
	else
	{
		signal(SIGINT, ft_sigint_cat);
		signal(SIGQUIT, ft_sigint_cat);
	}
}

void    start_get_commmand(t_env *env)
{
	char buff[4096];
	int bytes_readen;

	bytes_readen = -1;
	ft_signal(1);
	while ((bytes_readen = read(0, buff, 4095)) > 0)
	{
		buff[bytes_readen - 1] = '\0';
		ft_signal(0);
		start_read_command(env_translator(buff, env), env);
		print_prompt(0);
		ft_signal(1);
	}
}

char    *command_remove_quote_etc(char *str)
{
	char *buff;
	char *ref;
	char *ref_str;
	int presence_of_34;
	int presence_of_39;

	presence_of_34 = -1;
	presence_of_39 = -1;
	if (!(buff = malloc(sizeof(char) * ft_strlen(str) + 2)))
		return (NULL);
	ref = buff;
	ref_str = str;
	while (*str)
	{
		while (*str == 34 && presence_of_39 < 0)
		{
			if (((ref_str == str || *(str - 1) != 92) && presence_of_34 < 0) || (presence_of_34 > 0))
			{
				presence_of_34 *= -1;
				str++;
			}
			else
				break ;

		}
		while (*str == 39 && presence_of_34 < 0)
		{
			if (((ref_str == str || *(str - 1) != 92) && presence_of_39 < 0) || (presence_of_39 > 0))
			{
				presence_of_39 *= -1;
				str++;
			}
			else
				break ;
		}
		if (!(*str))
			break;
		if (*(str) == 92)
		{
			str++;
			*buff = *str;
			buff++;
			if (*str)
				str++;
		}
		else
		{
			*buff = *str;
			str++;
			buff++;
		}
	}
	*buff = '\0';
	return (ref);
}

void    command_read(char *buff, t_env *env)
{
	char *name_cmd;

	name_cmd = command_name_with_or_without_quote(buff);
	if (buff[0] == '\0')
	{
		env->last_program_return = 0;
		return ;
	}
	else if (buff[0] != '\0' && check_if_quote_are_close(buff))
	{
		printf_error(env->prog_name, 0, buff, "Quote are not closed");
		env->last_program_return = 1;
		return ;
	}
	env->ac = get_function_args(buff);
	if (buff[0] != '\0' && ft_strncmp(name_cmd, "exit", 5) == 0)
		ft_exit(env);
	else if (ft_strncmp(name_cmd, "pwd", 4) == 0)
		pwd(env, buff);
	else if (ft_strncmp(name_cmd, "cd", 3) == 0)
		cd_split(env);
	else if (ft_strncmp(name_cmd, "env", 4) == 0)
		display_env_list(env);
	else if (ft_strncmp(name_cmd, "unset", 6) == 0)
		unset(env, name_cmd, command_remove_quote_etc(buff));
	else if (ft_strncmp(name_cmd, "export", 7) == 0)
		export_env(env, name_cmd, command_remove_quote_etc(buff));
	else if (ft_strncmp(name_cmd, "echo", 5) == 0)
		echo_main(buff, env->ac, env);
	else if (buff[0] != '\0' && command_path_to_file_with_env(name_cmd, env) == 0)
		execute_env_binary_file(name_cmd, buff, env);
	else if (is_command_path_to_file(name_cmd) != -1)
	{
		if (is_command_path_to_file(name_cmd) == 2)
			printf_error(env->prog_name, 0, "is a directory", name_cmd);
		else
			execute_binary_file(name_cmd, remove_quote_arg(buff), env);
		env->last_program_return = 0;
	}
	else
	{
		printf_error(env->prog_name, 0, command_remove_quote_etc(name_cmd), "Command not found");
		env->last_program_return = 127;
	}
	ft_free(&name_cmd);
}

int     check_if_quote_are_close(char *str)
{
	int presence_of_34;
	int presence_of_39;

	presence_of_34 = -1;
	presence_of_39 = -1;
	while (*str)
	{
		if (*str == 34 && presence_of_39 < 0)
			presence_of_34 *= -1;
		if (*str == 39 && presence_of_34 < 0)
			presence_of_39 *= -1;
		if (presence_of_39 < 0 && presence_of_34 < 0)
			if (*str == 92 && *(str + 1) != '\0')
				str += 1;
		str++;
	}
	if (*(str - 1) == 92 && ft_strlen(str) > 1 && *(str - 2) != 92)
		return (1);
	if (presence_of_39 < 0 && presence_of_34 < 0)
		return (0);
	return (1);
}
