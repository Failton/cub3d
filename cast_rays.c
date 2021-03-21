/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:14:14 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/21 19:14:15 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void            cast_ray_set_def(double *x, double *y, t_all *all)
{
    all->point.h_x = all->plr.x;
    all->point.h_y = all->plr.y;
    all->point.v_x = all->plr.x;
    all->point.v_y = all->plr.y;
    *x = all->plr.x;
    *y = all->plr.y;
}

void            cast_ray_next(double *x, double *y, t_all *all)
{
    if (all->point.h_len < all->point.v_len)
    {
        *x = all->point.h_x;
        *y = all->point.h_y;
        all->point.h_flag = 1;
        all->point.v_flag = 0;
        horizont_point(all);
    }
    else
    {
        *x = all->point.v_x;
        *y = all->point.v_y;
        all->point.h_flag = 0;
        all->point.v_flag = 1;
        vertical_point(all);
    }
}

void            select_texture(t_all *all, int i, double x, double y)
{
    if (all->point.v_flag == 1
            && ((all->plr.ray_start >= -M_PI_2 && all->plr.ray_start <= M_PI_2)
                || (all->plr.ray_start <= -3 * M_PI_2
                    && all->plr.ray_start >= -2 * M_PI)))
        put_image_e(all, i, x, y);
    else if (all->point.v_flag == 1)
        put_image_w(all, i, x, y);
    else if (all->point.h_flag == 1
            && ((all->plr.ray_start >= -M_PI && all->plr.ray_start <= 0)
                || (all->plr.ray_start >= M_PI
                    && all->plr.ray_start <= 3 * M_PI_2)))
        put_image_n(all, i, x, y);
    else
        put_image_s(all, i, x, y);
}

void            cast_ray(t_all *all)
{
    double    x;
    double    y;
    int        i;

    i = -1;
    all->plr.ray_end = all->plr.dir + M_PI / 6;
    all->plr.ray_start = all->plr.dir - M_PI / 6;
    cast_ray_set_def(&x, &y, all);
    while (all->plr.ray_start <= all->plr.ray_end && ++i < all->width)
    {
        horizont_point(all);
        vertical_point(all);
        all->point.h_flag = 0;
        all->point.v_flag = 0;
        while (all->map[(int)(y / SCALE)][(int)(x / SCALE)] != '1')
        {
            if (all->map[(int)(y / SCALE)][(int)(x / SCALE)] == '2')
                put_sprite(all, i, x, y);
            cast_ray_next(&x, &y, all);
        }
        select_texture(all, i, x, y);
        all->plr.ray_start = -atan((all->width / 2 - i + 1) /
                (sqrt(3) * (all->width / 2))) + all->plr.dir;
        cast_ray_set_def(&x, &y, all);
    }
}
