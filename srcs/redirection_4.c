/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:01:47 by nveron            #+#    #+#             */
/*   Updated: 2020/09/10 16:42:10 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_error_open(t_cmdlist *list, char *cmd)
{
	int i;

	i = open(cmd, O_RDONLY, 0666);
	if (i < 0)
	{
		list->check_error = 1;
		ft_putstr_fd("./minishell: no such file or directory: ", 1);
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd("\n", 1);
	}
	return (i);
}

int			check_if_char_in_str_is_in_str2(char *charset, char *str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (charset[j] == str[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int			cut_cmd_for_pipe_and_redirection_malloc(char ***ac, char *str)
{
	int i;

	i = 0;
	if (!(*ac = malloc(sizeof(char*) * 4)))
		return (1);
	while (str[i] && check_if_char_is_in_str_modif(str, "<>|", i) != 1)
		i++;
	if (!((*ac)[0] = malloc(sizeof(char) * (i + 1))))
		return (1);
	if (!((*ac)[1] = malloc(sizeof(char) * (3))))
		return (1);
	str += i;
	i = 0;
	while (str[i] && check_if_char_is_in_str_modif(str, "<>|", i) == 1)
		i++;
	str += i;
	i = 0;
	while (str[i] && check_if_char_is_in_str_modif(str, "<>|", i) != 1)
		i++;
	if (!((*ac)[2] = malloc(sizeof(char) * (i + 1))))
		return (1);
	(*ac)[3] = NULL;
	return (0);
}

char		**cut_cmd_for_pipe_and_redirection(char **str)
{
	int		i;
	char	**ac;

	ac = NULL;
	if (cut_cmd_for_pipe_and_redirection_malloc(&ac, *str))
		return (NULL);
	i = cut_cmd_for_pipe_and_redirection_norme1(*str, ac, 1, 0);
	(*str) += i;
	i = cut_cmd_for_pipe_and_redirection_norme1(*str, ac, 0, 1);
	(*str) += i;
	i = cut_cmd_for_pipe_and_redirection_norme1(*str, ac, 1, 2);
	while (**str == ' ')
		(*str)++;
	return (ac);
}

void		ft_free_ac(char **ac)
{
	if (ac == NULL)
		return ;
	if (ac[0])
	{
		free(ac[0]);
		ac[0] = NULL;
	}
	if (ac[1])
	{
		free(ac[1]);
		ac[1] = NULL;
	}
	if (ac[2])
	{
		free(ac[2]);
		ac[2] = NULL;
	}
	if (ac)
	{
		free(ac);
		ac = NULL;
	}
}
