/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:06:25 by nveron            #+#    #+#             */
/*   Updated: 2020/03/04 07:47:25 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_army_if_red_norm1(t_env *env, char *cop, char *str,
		t_list *command)
{
	(void)command;
	if (ft_strncmp(cop, "pwd", 3) == 0)
		ft_putstr_fd(pwd(env, str), 1);
	else if (ft_strncmp(cop, "echo", 4) == 0)
		ft_putstr_fd(echo_main(env, str), 1);
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
		ft_putstr_fd(display_env_list(env), 1);
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
		cop = ft_strjoin(" '", cop);
	result = ft_army_if_red(env, cop, str + tmp, commands);
	free(cop);
	cop = NULL;
	return (result);
}
