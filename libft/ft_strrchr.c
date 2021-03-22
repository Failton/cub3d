/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <pruth@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:30:45 by pruthann          #+#    #+#             */
/*   Updated: 2020/11/14 16:30:56 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	smbl;
	char	*str;
	int		len;

	len = 0;
	smbl = (char)c;
	str = (char*)s;
	while (str[len])
		len++;
	if (str[len] == smbl)
		return (&str[len]);
	while (len)
	{
		if (str[len - 1] == smbl)
			return (&str[len - 1]);
		len--;
	}
	return (0);
}
