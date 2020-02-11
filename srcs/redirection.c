/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:06:25 by nveron            #+#    #+#             */
/*   Updated: 2020/02/03 13:08:38 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_army_if_red(t_env *env, char *cop, char *str, t_list *command)
{
	if (ft_strncmp(cop, "cd", 2) == 0)
	{
		cd_split(env, str);
		return(NULL);
	}
	else if (ft_strncmp(cop, "export", 6) == 0)
	{
		export_env(env, cop, str);
		return(NULL);
	}
	else if (ft_strncmp(cop, "env", 3) == 0)
		return(display_env_list(env));
	else if (ft_strncmp(cop, "unset", 5) == 0)
		unset(env, cop, str);
	else if (ft_strncmp(cop, "pwd", 3) == 0)
		return(pwd(env, str));
	else if (ft_strncmp(cop, "echo", 4) == 0)
		return(echo_main(env, str));
	else if (ft_strncmp(cop, "exit", 4) == 0)
		return("exit");
	else if (is_command_path_to_file(cop) != -1)
	{
		if (is_command_path_to_file(cop) == 2)
			printf_error(env->prog_name, 0, "is a directory", cop);
		else
			return(execute_binary_file(cop, str, env));
	}
	else if (command_path_to_file_with_env(cop, env) == 0)
		return(execute_env_binary_file(cop, str, env));
	else
		printf_error(env->prog_name, 0, str, "Command not found");
    return (NULL);

}

char *red_cut(t_list *commands, t_env *env, char *str)
{
	char 	*cop;
	int 	i;
	int 	j;
	int 	tmp;
    char *result;

	j = 0;
	i = 0;
	if (!(cop = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i] == ' ')
		i++;
	tmp = i;
	while (str[i] && str[i] != ' '
	&& str[i] != ';' && str[i] != '\n')
	{
		cop[j] = str[i];
		i++;
		j++;
	}
	cop[j] = '\0';
	result = ft_army_if_red(env, cop, str + tmp, commands);
	free(cop);
	cop = NULL;
    return (result);
}

char *sort_with_red(t_list *commands, t_env *env, char *first, char *second)
{
    char *copy;
    int i;
	int fd;
	int oldfd;
	char *str;

    i = 0;
ft_putstr_fd("||",1);
	ft_putstr_fd(first,1);
	ft_putstr_fd("//",1);
	ft_putstr_fd(second,1);
	ft_putstr_fd("||",1);
	
    if(!(copy = malloc((ft_strlen(second) + 1) * sizeof(char))))
        return (NULL);
    while (second[i] && ft_check_red_char(second[i], "<>|") != 1)
    {
        copy[i] = second[i];
        i++;
    }
    copy[i] = '\0';
	i = 0;
	while (first[0] == ' ')
		first++;
	while (first[i] && first[i] != ' ')
		i++;
	first[i] = '\0';
	fd = open(first, O_WRONLY, 0666);

	if (fd > -1)
	{


	str = ft_strjoin("cat", copy);
	str = ft_strjoin(str, " > ");
	str = ft_strjoin(str, first);

					oldfd = dup(1);
					dup2(fd, 1);
					red_cut(commands, env, str);
					dup2(oldfd, 1);
					close(fd);
	}
	else
    	str = ft_strjoin(first, copy);
    return (str);
}

char    *red_name(char *str)
{
    int i;
    int j;
    char *copy;

    if(!(copy = malloc(ft_strlen(str) + 1 * sizeof(char))))
        return (NULL);
    i = 0;
    j = 0;
    while (str[i] && str[i] == ' ')
        i++;
    while (str[i] && str[i] != ' ' && ft_check_red_char(str[i], "<>|") != 1)
    {
        copy[j] = str[i];
        i++;
        j++;
    }
    copy[j] = '\0';
    return (copy);
}

void ft_red(t_list *commands, t_env *env, char *str)
{
	char *copy;
    char *result;
    int res;
	int i;
	int j;
    int fd;
	int oldfd;

	j = 0;
	i = 0;
    res = 0;
    result = NULL;
	if (!(copy = malloc((ft_strlen(str) + 1) * sizeof(char))))
		return ;
	while (str[i])
	{
		if (ft_check_red_char(str[i], "<>|") != 1)
		{
			copy[j] = str[i];
			j++;
		}
		else
		{
			copy[j] = '\0';
            if (ft_check_red_char((str + i)[0], "<") == 1)
			{
				if (result != NULL)
					result = ft_strjoin(result, sort_with_red(commands, env, copy, str + i + 1));
				else
		      		result = sort_with_red(commands, env, copy, str + i + 1);
                while (str[i + 1] && ft_check_red_char(str[i + 1], "<>|") != 1)
                    i++;
                if (result == NULL && ft_check_red(str + i + 1) == 0)
                    result = red_cut(commands, env, result);
		    }
		    else if (ft_check_red_char(str[i], ">") == 1 && ft_check_red_char(str[i + 1], ">") != 1)
		    {
					oldfd = dup(1);
                    fd = open(red_name(str + i + 1), O_WRONLY | O_CREAT, 0666);
					dup2(fd, 1);
					if (result != NULL)
						red_cut(commands, env, result);
					else
						red_cut(commands, env, copy);
					dup2(oldfd, 1);
					close(fd);
					if (ft_check_red(str + i + 1) == 0)
						while (str[i + 1] && ft_check_red_char(str[i + 1], "<>|") != 1)
                    		i++;
	    	}
			else if (ft_check_red_char(str[i], ">") == 1 && ft_check_red_char(str[i + 1], ">") == 1)
		    {
					oldfd = dup(1);
                    fd = open(red_name(str + i + 2), O_WRONLY | O_CREAT | O_APPEND, 0666);
					dup2(fd, 1);
					if (result != NULL)
						red_cut(commands, env, result);
					else
						red_cut(commands, env, copy);
					dup2(oldfd, 1);
					close(fd);
					i++;
					if (ft_check_red(str + i + 1) == 0)
						while (str[i + 1] && ft_check_red_char(str[i + 1], "<>|") != 1)
                    		i++;
	    	}
			j = 0;
		}
		i++;
	}
    free(copy);
}
