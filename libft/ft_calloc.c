/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <pruth@student.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:45:26 by pruthann          #+#    #+#             */
/*   Updated: 2021/01/25 14:05:09 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned int	total;
	char			*s;

	total = count * size;
	s = malloc(total);
	if (s == 0)
		return (0);
	while (total)
	{
		s[total - 1] = 0;
		total--;
	}
	return (s);
}
