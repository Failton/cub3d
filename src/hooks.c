/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:06:34 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/22 11:06:35 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			move_plr(int keycode, t_all *all)
{
	if (keycode == 13 || keycode == 119)
	{
		all->plr.x += cos(all->plr.dir) * 0.4 * SCALE;
		all->plr.y += sin(all->plr.dir) * 0.4 * SCALE;
	}
	if (keycode == 1 || keycode == 115)
	{
		all->plr.x -= cos(all->plr.dir) * 0.4 * SCALE;
		all->plr.y -= sin(all->plr.dir) * 0.4 * SCALE;
	}
	if (keycode == 0 || keycode == 97)
	{
		all->plr.x += sin(all->plr.dir) * 0.4 * SCALE;
		all->plr.y -= cos(all->plr.dir) * 0.4 * SCALE;
	}
	if (keycode == 2 || keycode == 100)
	{
		all->plr.x -= sin(all->plr.dir) * 0.4 * SCALE;
		all->plr.y += cos(all->plr.dir) * 0.4 * SCALE;
	}
	if (keycode == 124 || keycode == 65363)
		all->plr.dir += 0.15;
	if (keycode == 123 || keycode == 65361)
		all->plr.dir -= 0.15;
}

int				key_hook(int keycode, t_all *all)
{
	move_plr(keycode, all);
	if (all->plr.dir <= -3 * M_PI_2)
		all->plr.dir += 2 * M_PI;
	if (all->plr.dir >= M_PI)
		all->plr.dir -= 2 * M_PI;
	if (keycode == 65307 || keycode == 53)
		close_win(all);
	mlx_destroy_image(all->win.mlx, all->win.img);
	all->win.img = mlx_new_image(all->win.mlx, all->width, all->height);
	all->win.addr = mlx_get_data_addr(all->win.img, &all->win.bpp,
			&all->win.line_len, &all->win.end);
	cast_ray(all);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
	return (1);
}
