/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:18:43 by pruthann          #+#    #+#             */
/*   Updated: 2021/02/13 15:18:58 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "get_next_line.h"

# define SCALE 62 // условный размер каждого квадратика в карте

typedef struct	s_win //структура для окна
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_len;
	int			bpp;
	int			end;
	int			img_width;
	int			img_height;
}				  t_win;

typedef struct	s_point // структура для точки
{
	float			v_x;
	float			v_y;
	float			v_len;
	int			v_flag;
	float			h_x;
	float			h_y;
	float			h_len;
	int			h_flag;

}				  t_point;

typedef struct	s_plr //структура для игрока и луча
{
	float		x;
	float		y;
	float		dir;
	float		ray_start;
	float		ray_end;
}				  t_plr;



typedef struct	s_all // структура для всего вместе
{
	t_win		*win;
	t_win		*image_n;
	t_win		*image_s;
	t_win		*image_w;
	t_win		*image_e;
	t_win		*sprite;
	t_plr		*plr;
	char		**map;
}				  t_all;

#endif
