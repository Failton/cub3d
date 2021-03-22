/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <pruth@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:51:53 by pruthann          #+#    #+#             */
/*   Updated: 2020/11/20 12:24:56 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newsrc;
	char	*temp;
	int		len;

	len = 0;
	while (s1[len] != '\0')
		len++;
	newsrc = malloc((len + 1) * sizeof(*s1));
	if (newsrc == 0)
		return (NULL);
	temp = newsrc;
	while (*s1)
	{
		*newsrc = *s1;
		newsrc++;
		s1++;
	}
	*newsrc = '\0';
	return (temp);
}
