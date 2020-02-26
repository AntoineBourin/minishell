/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:35:56 by abourin           #+#    #+#             */
/*   Updated: 2020/02/26 10:50:01 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_name_by_value(char **res, t_env_variable *env, int begin_index,
							int end_index)
{
	int		length;
	char	*tmp;
	int		i;
	int		j;
	int		z;
	char	*content;

	if (env == NULL)
		length = 0;
	else
		length = ft_strlen(env->content) - ft_strlen(env->name);
	if (!(tmp = malloc(sizeof(char) * (ft_strlen(*res) + length + 1))))
		return ;
	content = env != NULL ? env->content : NULL;
	i = 0;
	j = 0;
	while ((*res)[i] && i < begin_index - 1)
	{
		tmp[i] = (*res)[i];
		i++;
	}
	z = i;
	while (content && content[j])
	{
		tmp[i] = content[j];
		i++;
		j++;
	}
	while ((*res)[z + end_index - begin_index + 1])
	{
		tmp[i] = (*res)[z + end_index - begin_index + 1];
		i++;
		z++;
	}
	tmp[i] = '\0';
	//free(*res); --> TODO free only when transform coming from $ENV, not ~ change directory
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

void	transform_input_by_last_program_result(char **res, int index, t_env *env)
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
