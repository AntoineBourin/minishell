/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:06:25 by abourin           #+#    #+#             */
/*   Updated: 2020/01/31 15:08:38 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_curr_path(t_env *env)
{
	ft_putstr_fd(env->curr_path, 1);
	ft_putstr_fd(" : ", 1);
}

void	command_read(t_env *env)
{
	char	buff[4096];
	int		bytes_readen;

	print_curr_path(env);
	while ((bytes_readen = read(0, buff, 4095)) > 0)
	{
		buff[bytes_readen] = '\0';
		if (ft_strncmp(buff, "cd", 2) == 0)
			cd_split(env, buff);
		//printf("bytes %d || buff : %s\n\n", bytes_readen, buff);		//au lieu de faire un printf, ici faire un trie pour envoyer la commande avec la fonction qui l'execute
		if (bytes_readen < 4095)
			print_curr_path(env);
	}
}

void	cd_split(t_env *env, char *buff)
{
	char *str;
	int i;
	int j;

	i = 3;
	j = 0;
	if ((!(str = malloc(ft_strlen(buff) * sizeof(char)))) || (buff[2] != ' '))
		return;
	while(buff[i])
	{
		str[j] = buff[i];
		i++;
		j++;
	}
	str[j - 1] = '\0';
	move(str, 0, env);	
}