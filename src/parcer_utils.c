/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:04:52 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/22 11:04:53 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_header(t_all *all)
{
	all->header.res = 0;
	all->header.no = 0;
	all->header.so = 0;
	all->header.we = 0;
	all->header.ea = 0;
	all->header.s = 0;
	all->header.f = 0;
	all->header.c = 0;
}

int		strs_len(char **strs)
{
	int len;

	len = 0;
	if (strs != 0)
		while (strs[len] != 0)
			len++;
	return (len);
}

void	free_strs(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs[i]);
	free(strs);
}

int		check_header_dublicates(t_all all)
{
	if (all.header.res > 1)
		return (0);
	if (all.header.no > 1)
		return (0);
	if (all.header.so > 1)
		return (0);
	if (all.header.we > 1)
		return (0);
	if (all.header.ea > 1)
		return (0);
	if (all.header.s > 1)
		return (0);
	if (all.header.f > 1)
		return (0);
	if (all.header.c > 1)
		return (0);
	return (1);
}

char	*check_header(t_all all)
{
	if (all.header.res != 1)
		return (CONF);
	if (all.header.no != 1)
		return (CONF);
	if (all.header.so != 1)
		return (CONF);
	if (all.header.we != 1)
		return (CONF);
	if (all.header.ea != 1)
		return (CONF);
	if (all.header.s != 1)
		return (CONF);
	if (all.header.f != 1)
		return (CONF);
	if (all.header.c != 1)
		return (CONF);
	return ("1");
}
