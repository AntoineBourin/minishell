/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:35:56 by abourin           #+#    #+#             */
/*   Updated: 2020/10/04 22:16:00 by cnotin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **t, char **full_paths)
{
	ft_free_tab(t);
	ft_free_tab(full_paths);
}

void	transform_res_env_input(char **res, int index, t_env *env)
{
	int		begin_index;
	int		end_index;
	char	*env_name;
	char	*input;

	begin_index = index;
	input = *res;
	while (input[index] && ((input[index] >= 'a' && input[index] <= 'z')
	|| (input[index] >= 'A' && input[index] <= 'Z')))
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
	if (WEXITSTATUS(env->last_program_return))
		question_mark.content = ft_itoa(WEXITSTATUS(env->last_program_return));
	else
		question_mark.content = ft_itoa(env->last_program_return);
	replace_env_name_by_value(res, &question_mark, index, index + 1);
}

int		check_quote(char c, int i)
{
	if (c == 39)
		return (i * -1);
	return (i);
}

char	*env_translator(char *user_input, t_env *env)
{
	int		i;
	int		quote;
	char	*res;

	quote = -1;
	i = 0;
	if (!(res = malloc(sizeof(char) * ft_strlen(user_input) + 1)))
		return (NULL);
	ft_memcpy(res, user_input, ft_strlen(user_input));
	res[ft_strlen(user_input)] = '\0';
	while (res && res[i++])
	{
		quote = check_quote(res[i], quote);
		if (res[i] == '$' && (i > 0 && res[i - 1] != '\\') &&
				res[i + 1] != '\0' && quote < 0)
		{
			if (res[i + 1] && res[i + 1] == '?')
				transform_input_by_last_program_result(&res, i + 1, env);
			else
				transform_res_env_input(&res, i + 1, env);
			i = 0;
			continue;
		}
	}
	return (res);
}
