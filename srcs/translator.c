/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:35:56 by abourin           #+#    #+#             */
/*   Updated: 2020/02/29 11:49:48 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_name_by_value(char **res, t_env_variable *env,
		int begin_index, int end_index)
{
	int		length;
	char	*tmp;
	char	*content;
	t_comp	c1;

	replace_env_norm2(&length, env);
	if (!(tmp = malloc(sizeof(char) * (ft_strlen(*res) + length + 1))))
		return ;
	content = env != NULL ? env->content : NULL;
	replace_env_norm1(&res, &c1, begin_index, &tmp);
	while (content && content[c1.j])
	{
		tmp[c1.i] = content[c1.j];
		(c1.i)++;
		(c1.j)++;
	}
	while ((*res)[c1.k + end_index - begin_index + 1])
	{
		tmp[c1.i] = (*res)[c1.k + end_index - begin_index + 1];
		(c1.i)++;
		(c1.k)++;
	}
	tmp[c1.i] = '\0';
	*res = tmp;
}

void	transform_res_env_input(char **res, int index, t_env *env)
{
	int		begin_index;
	int		end_index;
	char	*env_name;
	char	*input;

	begin_index = index;
	input = *res;
	while (input[index])
		index++;
	end_index = index;
	if (!(env_name = malloc(sizeof(char) * (end_index - begin_index + 1))))
		return ;
	env_name[end_index - begin_index] = '\0';
	ft_memcpy(env_name, input + begin_index, end_index - begin_index);
	replace_env_name_by_value(res, get_env_variable_if_exist(env->env_variables,
									env_name), begin_index, end_index);
	free(env_name);
}

void	transform_input_by_last_program_result(char **res,
		int index, t_env *env)
{
	t_env_variable	question_mark;

	question_mark.name = "?";
	question_mark.content = ft_itoa(WEXITSTATUS(env->last_program_return));
	replace_env_name_by_value(res, &question_mark, index, index + 1);
}

char	*env_translator(char *user_input, t_env *env)
{
	int		i;
	char	*res;

	if (!(res = malloc(sizeof(char) * ft_strlen(user_input) + 1)))
		return (NULL);
	ft_memcpy(res, user_input, ft_strlen(user_input));
	res[ft_strlen(user_input)] = '\0';
	i = 0;
	while (res && res[i])
	{
		if (res[i] == '$' && res[i + 1] != '\0')
		{
			if (res[i + 1] && res[i + 1] == '?')
				transform_input_by_last_program_result(&res, i + 1, env);
			else
				transform_res_env_input(&res, i + 1, env);
			i = 0;
			continue;
		}
		i++;
	}
	return (res);
}
