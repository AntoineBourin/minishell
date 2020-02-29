/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:06:25 by nveron            #+#    #+#             */
/*   Updated: 2020/02/29 12:28:37 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_army_if_red_norm1(t_env *env, char *cop, char *str,
		t_list *command)
{
	(void)command;
	if (ft_strncmp(cop, "pwd", 3) == 0)
		return (pwd(env, str));
	else if (ft_strncmp(cop, "echo", 4) == 0)
		return (echo_main(env, str));
	else if (ft_strncmp(cop, "exit", 4) == 0)
		return ("exit");
	else if (is_command_path_to_file(cop) != -1)
	{
		if (is_command_path_to_file(cop) == 2)
			printf_error(env->prog_name, 0, "is a directory", cop);
		else
			return (execute_binary_file(cop, str, env));
	}
	else if (command_path_to_file_with_env(cop, env) == 0)
		return (execute_env_binary_file(cop, str, env));
	else
		printf_error(env->prog_name, 0, str, "Command not found");
	return (NULL);
}

char	*ft_army_if_red(t_env *env, char *cop, char *str, t_list *command)
{
	if (cop[0] == 34 || cop[0] == 39)
	{
		str++;
		cop++;
	}
	if (cop[0] == 34 || cop[0] == 39)
		cop++;
	if (ft_strncmp(cop, "cd", 2) == 0)
	{
		cd_split(env, str);
		return (NULL);
	}
	else if (ft_strncmp(cop, "export", 6) == 0)
	{
		export_env(env, cop, str);
		return (NULL);
	}
	else if (ft_strncmp(cop, "env", 3) == 0)
		return (display_env_list(env));
	else if (ft_strncmp(cop, "unset", 5) == 0)
		unset(env, cop, str);
	else
		return (ft_army_if_red_norm1(env, cop, str, command));
	return (NULL);
}

void	red_cut_norm1(t_comp *c1, char **str, char **cop)
{
	if ((*str)[c1->i + 1] == 34 || (*str)[c1->i + 1] == 39)
	{
		if ((*str)[c1->i + 1] == 34)
			c1->exp_1 *= -1;
		if ((*str)[c1->i + 1] == 39)
			c1->exp_2 *= -1;
		(*cop)[c1->j + 1] = ' ';
		(*str)[c1->i + 1] = ' ';
	}
	(*cop)[c1->j] = (*str)[c1->i];
	(c1->i)++;
	(c1->j)++;
}

void	red_cut_norm2(t_comp *c1, char *str, int *tmp)
{
	while (str[c1->i] == ' ')
		(c1->i)++;
	(*tmp) = c1->i;
	if (str[c1->i] == 34)
		c1->exp_1 *= -1;
	if (str[c1->i] == 39)
		c1->exp_2 *= -1;
}

char	*red_cut(t_list *commands, t_env *env, char *str)
{
	int		tmp;
	char	*cop;
	char	*result;
	t_comp	c1;

	c1.j = 0;
	c1.i = 0;
	c1.exp_1 = -1;
	c1.exp_2 = -1;
	if (!(cop = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	red_cut_norm2(&c1, str, &tmp);
	while (str[c1.i] && ((c1.exp_1 > 0 || c1.exp_2 > 0) ||
				(str[c1.i] != ' ' && str[c1.i] != '\n')))
		red_cut_norm1(&c1, &str, &cop);
	cop[c1.j] = '\0';
	if (c1.exp_1 > 0 || c1.exp_2 > 0)
		cop = ft_strjoin(ft_strjoin(" ", "'"), cop);
	result = ft_army_if_red(env, cop, str + tmp, commands);
	free(cop);
	cop = NULL;
	return (result);
}

char	*sort_with_red_norm1(t_list *commands,
		t_env *env, char **copy, char *first)
{
	int		fd;
	int		oldfd;
	char	*str;

	if (env->check_sign == 1)
		fd = open(first, O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0666);
	else
		fd = open(first, O_WRONLY | O_APPEND | O_TRUNC, 0666);
	if (fd > 0)
	{
		str = ft_strjoin("cat ", (*copy));
		oldfd = dup(1);
		dup2(fd, 1);
		red_cut(commands, env, str);
		dup2(oldfd, 1);
		close(fd);
	}
	else
		str = ft_strjoin(first, (*copy));
	free((*copy));
	return (str);
}

char	*sort_with_red(t_list *commands, t_env *env,
		char *first, char *second)
{
	int		i;
	char	*copy;

	i = 0;
	if (!(copy = malloc((ft_strlen(second) + 1) * sizeof(char))))
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
	return (sort_with_red_norm1(commands, env, &copy, first));
}

char	*red_name(char *str)
{
	int		i;
	int		j;
	char	*copy;

	if (!(copy = malloc(ft_strlen(str) + 1 * sizeof(char))))
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

char	*check_exeption_chiante(char *ref, char *str, char *name)
{
	int		i;
	int		j;
	char	*new;

	(void)name;
	if (!(new = malloc((ft_strlen(ref) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (*str && *str == ' ')
		str++;
	while (*str && *str != ' ')
		str++;
	while (str[i] && ft_check_red_char(str[i + 1], "<>|") != 1)
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	str = ft_strjoin(ref, new);
	return (str);
}

int		check_before(char *str, int i, char c)
{
	while (i > 0)
	{
		if (str[i] == c)
			return (1);
		i--;
	}
	return (0);
}

void	ft_red_norm1(char *str, t_comp *c1, t_list *commands, t_env *env)
{
	int fd;
	int oldfd;

	oldfd = dup(1);
	env->check_sign = 1;
	if ((!check_before(str, c1->i - 1, '>')
	&& !check_before(str, c1->i - 1, '|')) ||
(check_before(str, c1->i - 1, '>') && check_before(str, c1->i - 1, '|')))
	{
		fd = open(red_name(str + c1->i + 1), O_CREAT | O_WRONLY
		| O_TRUNC, 0666);
		dup2(fd, 1);
		if (c1->res != NULL)
			ft_putstr_fd(red_cut(commands, env, c1->res), 1);
		else
			ft_putstr_fd(red_cut(commands, env,
check_exeption_chiante(c1->cop, str + c1->i + 1, "D")), 1);
		dup2(oldfd, 1);
		close(fd);
	}
	else
		sort_with_red(commands, env, str + c1->i + 1, c1->cop);
	if (ft_check_red(str + c1->i + 1, "<>|") == 0)
		while (str[c1->i + 1] && ft_check_red_char(str[c1->i + 1], "<>|") != 1)
			(c1->i)++;
}

void	ft_red_norm2(char *str, t_comp *c1, t_list *commands, t_env *env)
{
	int fd;
	int oldfd;

	oldfd = dup(1);
	env->check_sign = 1;
	if ((!check_before(str, c1->i - 1, '>') &&
!check_before(str, c1->i - 1, '|')) || (check_before(str, c1->i - 1, '>')
	&& check_before(str, c1->i - 1, '|')))
	{
		fd = open(red_name(str + c1->i + 2), O_CREAT | O_WRONLY
	| O_APPEND, 0666);
		dup2(fd, 1);
		if (c1->res != NULL)
			ft_putstr_fd(red_cut(commands, env, c1->res), 1);
		else
			ft_putstr_fd(red_cut(commands, env, c1->cop), 1);
		dup2(oldfd, 1);
		close(fd);
	}
	else
		sort_with_red(commands, env, str + c1->i + 2, c1->cop);
	(c1->i)++;
	if (ft_check_red(str + c1->i + 1, "<>|") == 0)
		while (str[c1->i + 1] && ft_check_red_char(str[c1->i + 1], "<>|") != 1)
			(c1->i)++;
}

void	ft_red_norm3(t_comp *c1, t_list *commands, t_env *env, char *str)
{
	if (c1->res != NULL)
		c1->res = ft_strjoin(c1->res, sort_with_red(commands,
		env, c1->cop, str + c1->i + 1));
	else
		c1->res = sort_with_red(commands, env, c1->cop, str + c1->i + 1);
	while (str[c1->i] && str[c1->i + 1] && ft_check_red(str + c1->i + 1,
	"<>|") != 0 && ft_check_red_char(str[c1->i + 1], "<>|") != 1)
		(c1->i)++;
	if (ft_check_red(str + c1->i + 1, "<>|") == 0)
		c1->res = red_cut(commands, env, c1->res);
}

int		ft_red_norm4(t_comp *c1, char *str, char **copy, t_env *env)
{
	c1->j = 0;
	c1->i = 0;
	c1->res = NULL;
	env->check_sign = 0;
	if (!((*copy) = malloc((ft_strlen(str) + 1) * sizeof(char))))
		return (1);
	return (0);
}

void	ft_red_norm5(char **copy, t_comp *c1, char *str)
{
	(*copy)[c1->j] = str[c1->i];
	(c1->j)++;
}

void	ft_red_norm6(t_comp *c1, t_list *commands, t_env *env, char *str)
{
	c1->i += execute_pipes_command(commands, env, c1->cop,
	str + c1->i - (ft_strlen(c1->cop) + 1));
	c1->i -= (ft_strlen(c1->cop) + 1);
}

void	ft_red_norm7(char *str, t_comp *c1, t_list *commands, t_env *env)
{
	if (ft_check_red_char(str[c1->i], "<") == 1)
		ft_red_norm3(c1, commands, env, str);
	else if (ft_check_red_char(str[c1->i], ">") == 1 &&
	ft_check_red_char(str[c1->i + 1], ">") != 1)
		ft_red_norm1(str, c1, commands, env);
	else if (ft_check_red_char(str[c1->i], ">") == 1 &&
	ft_check_red_char(str[c1->i + 1], ">") == 1)
		ft_red_norm2(str, c1, commands, env);
	else if (ft_check_red_char(str[c1->i], "|") == 1)
		ft_red_norm6(c1, commands, env, str);
}

void	ft_red(t_list *commands, t_env *env, char *str)
{
	char	*copy;
	t_comp	c1;

	if (ft_red_norm4(&c1, str, &copy, env) > 0)
		return ;
	while (str[c1.i])
	{
		if (ft_check_red_char(str[c1.i], "<>|") != 1)
			ft_red_norm5(&copy, &c1, str);
		else
		{
			while (c1.j > 1 && copy[c1.j] && copy[c1.j - 1]
			&& copy[c1.j - 1] == ' ')
				(c1.j)--;
			copy[c1.j] = '\0';
			c1.cop = copy;
			ft_red_norm7(str, &c1, commands, env);
			c1.j = 0;
		}
		(c1.i)++;
	}
	free(copy);
}
