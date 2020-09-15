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

int			number_of_split(char *str)
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

int			is_a_separator(char *str, int j)
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

void		split_modif_norm1(int *i, int *j, char **str, char **cmd)
{
	while (**str && **str == ' ')
		(*str)++;
	while ((*str)[*i] && is_a_separator(*str, *i) != 1)
	{
		cmd[*j][*i] = (*str)[*i];
		(*i)++;
	}
	cmd[*j][*i] = '\0';
	(*j)++;
	(*str) += (*i);
	if (**str == ';')
		(*str)++;
}

char		**split_modif(char *str)
{
	char	**cmd;
	int		j;
	int		i;

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
		split_modif_norm1(&i, &j, &str, cmd);
		i = 0;
	}
	cmd[j] = NULL;
	return (cmd);
}

int			check_norm_1(char *str, int *i, int *j, char *charset)
{
	if (str[*i] == 92 && str[(*i) + 1] != '\0')
		(*i)++;
	else
	{
		while (charset[(*j)])
		{
			if (charset[*j] == str[*i])
				return (1);
			(*j)++;
		}
	}
	return (0);
}
