/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:04:18 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/24 19:02:49 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		quantity_comma(char *str)
{
	int i;
	int total;

	i = 0;
	total = 0;
	while (str[i] != 0)
	{
		if (str[i] == ',')
			total++;
		i++;
	}
	return (total);
}

int		check_one_num(char *str)
{
	char	**strs;
	int		num;

	strs = ft_split(str, ' ');
	if (strs_len(strs) != 1)
		return (-1);
	num = ft_atoi(strs[0]);
	free_strs(strs);
	return (num);
}

char	*check_fill_res(int i, t_all *all, int argc)
{
	int		j;
	char	**strs;
	int		resx;
	int		resy;

	j = 0;
	while (all->map[i][++j] != 0)
		if ((all->map[i][j] < '0' || all->map[i][j] > '9')
				&& all->map[i][j] != ' ')
			return (RES);
	strs = ft_split(all->map[i], ' ');
	if (strs_len(strs) != 3)
		return (RES);
	all->width = ft_atoi(strs[1]);
	all->height = ft_atoi(strs[2]);
	mlx_get_screen_size(all->win.mlx, &resx, &resy);
	if (all->width > resx && argc == 2)
		all->width = resx;
	if (all->height > resy && argc == 2)
		all->height = resy;
	if (all->width <= 0 || all->height <= 0)
		return (RES);
	free_strs(strs);
	all->header.res++;
	return ("1");
}

char	*check_fill_f(int i, t_all *all)
{
	char	**strs;
	char	*str;
	int		r;
	int		g;
	int		b;

	r = 0;
	while (all->map[i][++r] != 0)
		if ((all->map[i][r] < '0' || all->map[i][r] > '9')
				&& all->map[i][r] != ' ' && all->map[i][r] != ',')
			return (FLOOR);
	str = all->map[i] + 1;
	strs = ft_split(str, ',');
	if (strs_len(strs) != 3 || quantity_comma(str) != 2)
		return (FLOOR);
	r = check_one_num(strs[0]);
	g = check_one_num(strs[1]);
	b = check_one_num(strs[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (FLOOR);
	all->floor_color = create_trgb(0, r, g, b);
	free_strs(strs);
	all->header.f++;
	return ("1");
}

char	*check_fill_c(int i, t_all *all)
{
	char	**strs;
	char	*str;
	int		r;
	int		g;
	int		b;

	r = 0;
	while (all->map[i][++r] != 0)
		if ((all->map[i][r] < '0' || all->map[i][r] > '9')
				&& all->map[i][r] != ' ' && all->map[i][r] != ',')
			return (CEIL);
	str = all->map[i] + 1;
	strs = ft_split(str, ',');
	if (strs_len(strs) != 3 || quantity_comma(str) != 2)
		return (CEIL);
	r = check_one_num(strs[0]);
	g = check_one_num(strs[1]);
	b = check_one_num(strs[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (CEIL);
	all->ceil_color = create_trgb(0, r, g, b);
	free_strs(strs);
	all->header.c++;
	return ("1");
}
