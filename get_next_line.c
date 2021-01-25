/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <pruth@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:57:57 by pruthann          #+#    #+#             */
/*   Updated: 2021/01/25 12:36:50 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int		join_checker(char **buf, char **rem, char **line, int i)
{
	int answer;

	if (i == 0)
		answer = ft_strjoin_free(line, *rem);
	else
		answer = ft_strjoin_free(line, *buf);
	if (answer == -1)
	{
		free(*buf);
		free(*rem);
		*rem = NULL;
		return (-1);
	}
	return (1);
}

int		main_checks(char **buf, char **rem, char **line)
{
	if (BUFFER_SIZE < 1 || line == NULL)
		return (-1);
	*buf = malloc(sizeof(char*) * (BUFFER_SIZE + 1));
	if (*buf == 0)
		return (-1);
	if (*rem == 0)
	{
		*rem = malloc(sizeof(char*) * (BUFFER_SIZE + 1));
		if (*rem == 0)
		{
			free(*buf);
			return (-1);
		}
		rem[0][0] = '\0';
	}
	return (1);
}

int		quantity_checker(char **buf, char **rem, int quantity)
{
	if (quantity < 1)
	{
		free(*buf);
		free(*rem);
		*rem = NULL;
		return (quantity);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*rem;
	int			quantity;
	int			a;

	if (main_checks(&buf, &rem, line) == -1)
		return (-1);
	*line = NULL;
	if (join_checker(&buf, &rem, line, 0) == -1)
		return (-1);
	a = check_endl(rem);
	ft_strcpy(&rem, rem, a);
	while (a < 0)
	{
		quantity = read(fd, buf, BUFFER_SIZE);
		if (quantity_checker(&buf, &rem, quantity) < 1)
			return (quantity);
		buf[quantity] = '\0';
		a = check_endl(buf);
		ft_strcpy(&rem, buf, a);
		if (join_checker(&buf, &rem, line, 1) == -1)
			return (-1);
	}
	free(buf);
	return (1);
}
