/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:16:32 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/21 17:19:32 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			choose_dir(t_all *all, int i, int j)
{
	if (all->map[i][j] == 'E')
		all->plr.dir = 0;
	else if (all->map[i][j] == 'S')
		all->plr.dir = M_PI_2;
	else if (all->map[i][j] == 'W')
		all->plr.dir = 3.1415;
	else if (all->map[i][j] == 'N')
		all->plr.dir = -M_PI_2;
}



void			tan_exp_f(t_all *all, double *x1, double *x2)
{
	*x2 = *x1 + tan(all->plr.dir) * SCALE;
	if ((all->plr.dir >= 0 && all->plr.dir <= M_PI_2) ||
	(all->plr.dir >= -M_PI && all->plr.dir <= -M_PI_2))
		*x2 = *x1 - tan(all->plr.dir) * SCALE;
}

void			tan_exp_s(t_all *all, double *y1, double *y2)
{
	*y2 = *y1 + 1 / tan(all->plr.dir) * SCALE;
	if (all->plr.dir == 0 || all->plr.dir == -3.1415 || all->plr.dir == 3.1415)
		*y2 = *y1 + SCALE;
}

void			dot_x_y(t_all *all, double *x3, double *y3)
{
	*x3 = all->plr.x + cos(all->plr.ray_start) * SCALE;
	*y3 = all->plr.y + sin(all->plr.ray_start) * SCALE;
}

void			find_line(t_all *all, double *x1, double *y1)
{
	double	x2;
	double	y2;
	double	x3;
	double	y3;

	tan_exp_f(all, x1, &x2);
	tan_exp_s(all, y1, &y2);
	dot_x_y(all, &x3, &y3);
	if ((int)((((*y1 - y2) * (all->plr.x * y3 - x3 * all->plr.y) -
	(all->plr.y - y3) * (*x1 * y2 - x2 * *y1)) / ((all->plr.y - y3) * (x2 - *x1)
	- (*y1 - y2) * (x3 - all->plr.x))) / SCALE) == (int)(*y1 / SCALE))
		*y1 = ((*y1 - y2) * (all->plr.x * y3 - x3 * all->plr.y) -
		(all->plr.y - y3) * (*x1 * y2 - x2 * *y1)) / ((all->plr.y - y3) *
		(x2 - *x1) - (*y1 - y2) * (x3 - all->plr.x));
	else
		*y1 = -1;
	if ((int)((-((x3 - all->plr.x) / (all->plr.y - y3)) * *y1 -
	((all->plr.x * y3 - x3 * all->plr.y) / (all->plr.y - y3))) /
	SCALE) == (int)(*x1 / SCALE))
		*x1 = -((x3 - all->plr.x) / (all->plr.y - y3)) * *y1 -
		((all->plr.x * y3 - x3 * all->plr.y) / (all->plr.y - y3));
	else if ((all->plr.y - y3) == 0)
		*x1 = *x1;
	else
		*x1 = -1;
}

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
