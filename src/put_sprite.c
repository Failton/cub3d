/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:00:51 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/22 11:00:56 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				borders_cut(t_all *all, double tmp_x, double tmp_y)
{
	if (all->plr.dir >= -M_PI_4 && all->plr.dir <= M_PI_4 && (int)(((tmp_y -
	(int)(tmp_y / SCALE) * SCALE) - SCALE * (1 - fabs(cos(all->plr.dir)))) /
	fabs(cos(all->plr.dir)) / SCALE * all->sprite.img_width) < 0)
		return (0);
	else if (((all->plr.dir <= -3 * M_PI_4 && all->plr.dir >= -5 * M_PI_4) ||
	(all->plr.dir <= M_PI && all->plr.dir >= 3 * M_PI_4)) && (int)(((tmp_y -
	(int)(tmp_y / SCALE) * SCALE) - SCALE * (1 - fabs(cos(all->plr.dir)))) /
	fabs(cos(all->plr.dir)) / SCALE * all->sprite.img_width) - 1 < 0)
		return (0);
	else if (all->plr.dir >= -3 * M_PI_4 && all->plr.dir <= -M_PI_4 && (int)
	(((tmp_x - (int)(tmp_x / SCALE) * SCALE) - SCALE * (1 - fabs(sin(all->plr.
	dir)))) / fabs(sin(all->plr.dir)) / SCALE * all->sprite.img_width) < 0)
		return (0);
	else if (((all->plr.dir >= -3 * M_PI_2 && all->plr.dir <= -5 * M_PI_4) ||
	(all->plr.dir >= M_PI_4 && all->plr.dir <= 3 * M_PI_4)) && (int)(((tmp_x -
	(int)(tmp_x / SCALE) * SCALE) - SCALE * (1 - fabs(sin(all->plr.dir)))) /
	fabs(sin(all->plr.dir)) / SCALE * all->sprite.img_width) - 1 < 0)
		return (0);
	return (1);
}

void			line_len(t_all *all, double *tmp_x, double *tmp_y)
{
	all->line = SCALE * all->height / (hypot(all->plr.x - *tmp_x, all->plr.y -
	*tmp_y) * ((*tmp_x - all->plr.x) * (cos(all->plr.dir) * SCALE) + (*tmp_y -
	all->plr.y) * (sin(all->plr.dir) * SCALE)) / (hypot(*tmp_x - all->plr.x,
	*tmp_y - all->plr.y) * hypot(cos(all->plr.dir) * SCALE, sin(all->plr.dir)
	* SCALE)));
	find_line(all, tmp_x, tmp_y);
	if (all->line >= all->height)
		all->line = 0;
}

int				color_f_part(t_all *all, int k, double tmp_x, double tmp_y)
{
	if (tmp_y != -1 && tmp_x != -1 && all->plr.dir >= -M_PI_4 &&
	all->plr.dir <= M_PI_4)
	{
		all->color = my_mlx_get_color(all->sprite,
		(int)(((tmp_y - (int)(tmp_y / SCALE) * SCALE) - SCALE * (1 -
		fabs(cos(all->plr.dir)))) / fabs(cos(all->plr.dir)) / SCALE *
		all->sprite.img_width), (k - (all->height - all->line)
		/ 2) / (all->line / all->sprite.img_height));
		return (1);
	}
	else if (tmp_y != -1 && tmp_x != -1 && ((all->plr.dir <= -3 *
	M_PI_4 && all->plr.dir >= -5 * M_PI_4) ||
	(all->plr.dir <= M_PI && all->plr.dir >= 3 * M_PI_4)))
	{
		all->color = my_mlx_get_color(all->sprite, (int)(all->sprite.
		img_width - ((tmp_y - (int)(tmp_y / SCALE) * SCALE) - SCALE * (1 -
		fabs(cos(all->plr.dir)))) / fabs(cos(all->plr.dir)) / SCALE *
		all->sprite.img_width), (k - (all->height - all->line) / 2) /
		(all->line / all->sprite.img_height));
		return (1);
	}
	return (0);
}

int				color_s_part(t_all *all, int k, double tmp_x, double tmp_y)
{
	if (tmp_y != -1 && tmp_x != -1 && all->plr.dir >= -3 * M_PI_4
		&& all->plr.dir <= -M_PI_4)
	{
		all->color = my_mlx_get_color(all->sprite, (int)(((tmp_x - (int)
		(tmp_x / SCALE) * SCALE) - SCALE * (1 - fabs(sin(all->plr.dir)))) /
		fabs(sin(all->plr.dir)) / SCALE * all->sprite.img_width), (k -
		(all->height - all->line) / 2) / (all->line / all->sprite.img_height));
		return (1);
	}
	else if (tmp_y != -1 && tmp_x != -1)
	{
		all->color = my_mlx_get_color(all->sprite, (int)(all->sprite.
		img_width - ((tmp_x - (int)(tmp_x / SCALE) * SCALE) - SCALE * (1 -
		fabs(sin(all->plr.dir)))) / fabs(sin(all->plr.dir)) / SCALE * all->
		sprite.img_width), (k - (all->height - all->line) / 2) / (all->line /
		all->sprite.img_height));
		return (1);
	}
	return (0);
}

void			put_sprite(t_all *all, int i, double x, double y)
{
	int				k;
	double			tmp_x;
	double			tmp_y;

	k = -1;
	tmp_x = (int)(x / SCALE) * SCALE + SCALE / 2;
	tmp_y = (int)(y / SCALE) * SCALE + SCALE / 2;
	line_len(all, &tmp_x, &tmp_y);
	if (borders_cut(all, tmp_x, tmp_y) == 0)
		return ;
	while (k < (all->height - all->line) / 2)
		k++;
	k--;
	while (++k < all->line + (all->height - all->line) / 2)
	{
		if (color_f_part(all, k, tmp_x, tmp_y) == 0)
			color_s_part(all, k, tmp_x, tmp_y);
		if (all->color != 4278190080 && tmp_y != -1 && tmp_y != -1 &&
		my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->color);
	}
}
