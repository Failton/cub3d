/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:04:01 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/22 11:04:03 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			horizont_point(t_all *all)
{
	double	temp_x;
	double	temp_y;

	temp_x = all->point.h_x;
	temp_y = all->point.h_y;
	if ((all->plr.ray_start >= -M_PI && all->plr.ray_start <= 0) ||
			(all->plr.ray_start >= M_PI && all->plr.ray_start <= 3 * M_PI_2))
		all->point.h_y = (int)(temp_y / SCALE) * SCALE - 0.00009;
	else
		all->point.h_y = (int)(temp_y / SCALE) * SCALE + SCALE;
	all->point.h_x = temp_x - (temp_y - all->point.h_y) /
		tan(all->plr.ray_start);
	all->point.h_len = hypot(all->plr.x - all->point.h_x,
			all->plr.y - all->point.h_y);
}

void			vertical_point(t_all *all)
{
	double	temp_x;
	double	temp_y;

	temp_x = all->point.v_x;
	temp_y = all->point.v_y;
	if ((all->plr.ray_start >= -M_PI_2 && all->plr.ray_start <= M_PI_2) ||
			(all->plr.ray_start <= -3 * M_PI_2 &&
			all->plr.ray_start >= -2 * M_PI))
		all->point.v_x = (int)(temp_x / SCALE) * SCALE + SCALE;
	else
		all->point.v_x = (int)(temp_x / SCALE) * SCALE - 0.00009;
	all->point.v_y = temp_y - (temp_x - all->point.v_x) *
		tan(all->plr.ray_start);
	all->point.v_len = hypot(all->plr.x - all->point.v_x,
			all->plr.y - all->point.v_y);
}
