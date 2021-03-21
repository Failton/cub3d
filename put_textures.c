/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:15:35 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/21 19:15:36 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void            put_image_e(t_all *all, int i, double x, double y)
{
    int        k;
    double    line;
    double    black;

    k = -1;
    line = SCALE * all->height / (hypot(all->plr.x - x, all->plr.y - y)
    * fabs(cos(all->plr.ray_start - all->plr.dir)));
    if (line >= all->height)
        line = 0;
    black = (all->height - line) / 2;
    while (++k < black)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, all->floor_color);
    k--;
    while (++k < line + black)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, my_mlx_get_color(all->image_e,
            (int)((y - (int)(y / SCALE) * SCALE) / SCALE * all->image_e.
            img_width), (k - black) / (line / all->image_e.img_height)));
    k--;
    while (++k < black * 2 + line)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, all->ceil_color);
}

void            put_image_w(t_all *all, int i, double x, double y)
{
    int        k;
    double    line;
    double    black;

    k = -1;
    line = SCALE * all->height / (hypot(all->plr.x - x, all->plr.y - y)
    * fabs(cos(all->plr.ray_start - all->plr.dir)));
    if (line >= all->height)
        line = 0;
    black = (all->height - line) / 2;
    while (++k < black)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, all->floor_color);
    k--;
    while (++k < line + black)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, my_mlx_get_color(all->image_w,
            (int)(all->image_w.img_width - (y - (int)(y / SCALE) * SCALE) /
            SCALE * all->image_w.img_width), (k - black) / (line /
            all->image_w.img_height)));
    k--;
    while (++k < black * 2 + line)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, all->ceil_color);
}

void            put_image_n(t_all *all, int i, double x, double y)
{
    int        k;
    double    line;
    double    black;

    k = -1;
    line = SCALE * all->height / (hypot(all->plr.x - x, all->plr.y - y)
    * fabs(cos(all->plr.ray_start - all->plr.dir)));
    if (line >= all->height)
        line = 0;
    black = (all->height - line) / 2;
    while (++k < black)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, all->floor_color);
    k--;
    while (++k < line + black)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, my_mlx_get_color(all->image_n,
            (int)((x - (int)(x / SCALE) * SCALE) / SCALE * all->image_n.
            img_width), (k - black) / (line / all->image_n.img_height)));
    k--;
    while (++k < black * 2 + line)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, all->ceil_color);
}

void            put_image_s(t_all *all, int i, double x, double y)
{
    int        k;
    double    line;
    double    black;

    k = -1;
    line = SCALE * all->height / (hypot(all->plr.x - x, all->plr.y - y)
    * fabs(cos(all->plr.ray_start - all->plr.dir)));
    if (line >= all->height)
        line = 0;
    black = (all->height - line) / 2;
    while (++k < black)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, all->floor_color);
    k--;
    while (++k < line + black)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, my_mlx_get_color(all->image_s,
            (int)(all->image_s.img_width - (x - (int)(x / SCALE) * SCALE) /
            SCALE * all->image_s.img_width), (k - black) /
            (line / all->image_s.img_height)));
    k--;
    while (++k < black * 2 + line)
        if (my_mlx_get_color(all->win, i, k) == 0)
            my_mlx_pixel_put(all->win, i, k, all->ceil_color);
}
