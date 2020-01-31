/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:00:40 by nveron            #+#    #+#             */
/*   Updated: 2019/11/14 11:59:54 by nveron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_check(int fd, char **str)
{
	char	buff[32 + 1];
	int		size;
	char	*tmp;

	size = 1;
	while (size && (ft_strchr(*str, '\n') == 0))
	{
		size = read(fd, buff, 32);
		if (size < 0 || str == NULL)
			return (-1);
		if (fd >= 0)
		{
			buff[size] = '\0';
			tmp = ft_stridup(*str, 0);
			free(*str);
			*str = ft_strjoin(tmp, buff);
			free(tmp);
		}
	}
	return (size);
}

char	*ft_line(char **str, char *line)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	tmp = ft_stridup(*str, 0);
	while (j < i)
	{
		line[j] = (*str)[j];
		j++;
	}
	line[j] = '\0';
	free(*str);
	*str = NULL;
	if (tmp && tmp[i] != '\0')
		*str = ft_stridup(tmp, i + 1);
	if (tmp)
		free(tmp);
	return (line);
}

int		get_next_line(int fd, char **line)
{
	int			size;
	static char	*str;

	if (fd < 0 || !line)
		return (-1);
	if (str == NULL)
		str = ft_calloc(1, sizeof(char));
	size = ft_check(fd, &str);
	if (size < 0)
	{
		free(str);
		str = NULL;
		return (-1);
	}
	*line = ft_line(&str, *line);
	if (size == 0)
	{
		if (str)
		{
			free(str);
			str = NULL;
		}
		return (0);
	}
	return (1);
}
