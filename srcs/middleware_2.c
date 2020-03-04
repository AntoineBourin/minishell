/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middleware_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:12:05 by abourin           #+#    #+#             */
/*   Updated: 2020/03/04 07:46:26 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_army_if_norm1(t_env *env, char *cop,
		char *str, t_list *command)
{
	if (ft_strncmp(cop, "echo", 5) == 0)
		command->result = echo_main(env, str);
	else if (ft_strncmp(cop, "exit", 5) == 0)
		command->result = str;
	else if (is_command_path_to_file(cop) != -1)
	{
		if (is_command_path_to_file(cop) == 2)
			printf_error(env->prog_name, 0, "is a directory", cop);
		else
			command->result = execute_binary_file(cop, remove_quote_arg(str),
					env);
	}
	else if (command_path_to_file_with_env(cop, env) == 0)
		command->result = execute_env_binary_file(cop, remove_quote_arg(str),
				env);
	else
		printf_error(env->prog_name, 0, str, "Command not found");
}

static void		ft_army_if(t_env *env, char *cop, char *str, t_list *command)
{
	if (cop[0] == 34 || cop[0] == 39)
	{
		str++;
		cop++;
	}
	env->check = 0;
	if (ft_strncmp(cop, "cd", 3) == 0)
	{
		cd_split(env, str);
		command->result = NULL;
	}
	else if (ft_strncmp(cop, "export", 7) == 0)
	{
		command->result = export_env(env, cop, remove_quote_arg(str));
	}
	else if (ft_strncmp(cop, "env", 4) == 0)
		command->result = display_env_list(env);
	else if (ft_strncmp(cop, "unset", 6) == 0)
		unset(env, cop, str);
	else if (ft_strncmp(cop, "pwd", 4) == 0)
		command->result = pwd(env, str);
	else
		ft_army_if_norm1(env, cop, str, command);
}

void			ft_sort_norm1(t_comp *c1, char *str, int *tmp)
{
	while (str[c1->i] == ' ')
		(c1->i)++;
	(*tmp) = c1->i;
	if (str[c1->i] == 34)
		c1->exp_1 *= -1;
	if (str[c1->i] == 39)
		c1->exp_2 *= -1;
}

void			ft_sort_norm2(t_comp *c1, char **str, char **cop)
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

void			ft_sort(t_env *env, t_list *command)
{
	int		tmp;
	char	*cop;
	char	*str;
	t_comp	c1;

	c1.j = 0;
	c1.i = 0;
	c1.exp_1 = -1;
	c1.exp_2 = -1;
	str = command->content;
	if (!(cop = malloc(sizeof(char) * (ft_strlen(str) + 3))))
		return ;
	ft_sort_norm1(&c1, str, &tmp);
	while (str[c1.i] && ((c1.exp_1 > 0 || c1.exp_2 > 0) ||
				(str[c1.i] != ' ' && str[c1.i] != '\n')))
		ft_sort_norm2(&c1, &str, &cop);
	cop[c1.j] = '\0';
	if (c1.exp_1 > 0 || c1.exp_2 > 0)
		cop = ft_strjoin(ft_strjoin(" ", "'"), cop);
	ft_army_if(env, cop, str + tmp, command);
	free(cop);
	cop = NULL;
}
