/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/13 17:05:35 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*place_str_at_the_begin_command(char *str)
{
	int presence_of_34;
	int presence_of_39;

	presence_of_34 = -1;
	presence_of_39 = -1;
	while (*str == ' ')
		str++;
	while (*str == 34 || *str == 39)
	{
		if (*str == 34)
			presence_of_34 *= -1;
		if (*str == 39)
			presence_of_39 *= -1;
		if (presence_of_34 > 0 && presence_of_39 > 0)
			return (str - 1);
		str++;
	}
	if (presence_of_34 > 0 || presence_of_39 > 0)
		return (str - 1);
	else
		return (str);
}

char	*command_name_with_or_without_quote(char *str)
{
	str = place_str_at_the_begin_command(str);
	if (*str == 39)
		return (get_name_command_fonction_with_quote(str, 39));
	else if (*str == 34)
		return (get_name_command_fonction_with_quote(str, 34));
	else
		return (get_name_command_fonction_without_quote(str));
}

char	*get_name_command_fonction_with_quote(char *str, char quote)
{
	char	*name;
	int		i;

	i = 0;
	str++;
	while (str[i] && str[i] != quote)
		i++;
	if (!(name = malloc((sizeof(char) * i) + 1)))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != quote)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_name_command_fonction_without_quote(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (!(name = malloc((sizeof(char) * i) + 1)))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}
