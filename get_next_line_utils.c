/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <pruth@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:58:41 by pruthann          #+#    #+#             */
/*   Updated: 2021/01/25 14:27:03 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int		ft_strjoin_free(char **s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (str == 0)
		return (-1);
	if (*s1 != 0)
		while (s1[0][i])
		{
			str[i] = s1[0][i];
			i++;
		}
	while (s2[j] && s2[j] != '\n')
		str[i++] = s2[j++];
	str[i] = '\0';
	if (*s1 != 0)
		free(*s1);
	*s1 = str;
	return (1);
}

int		check_endl(char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_strcpy(char **dst, char *src, int a)
{
	int i;

	i = 0;
	a++;
	while (a < BUFFER_SIZE && a != 0)
	{
		dst[0][i] = src[a];
		a++;
		i++;
	}
	dst[0][i] = '\0';
}
