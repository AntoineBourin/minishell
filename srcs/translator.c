/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:35:56 by abourin           #+#    #+#             */
/*   Updated: 2020/02/06 15:54:52 by abourin          ###   ########.fr       */
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
	free(*res);
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
		if (res[i] == '$')
		{
			transform_res_env_input(&res, i + 1, env);
			i = 0;
		}
		i++;
	}
	return (res);
}
