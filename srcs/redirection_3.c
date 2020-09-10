/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:06:25 by nveron            #+#    #+#             */
/*   Updated: 2020/03/04 07:53:43 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
