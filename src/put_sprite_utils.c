/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:01:26 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/22 11:01:29 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
