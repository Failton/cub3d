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
	double			v_x;
	double			v_y;
	double			v_len;
	int			v_flag;
	double			h_x;
	double			h_y;
	double			h_len;
	int			h_flag;

}				  t_point;

typedef struct	s_plr //структура для игрока и луча
{
	double		x;
	double		y;
	double		dir;
	double		ray_start;
	double		ray_end;
}				  t_plr;



typedef struct	s_all // структура для всего вместе
{
	t_win		win;
	t_win		image_n;
	t_win		image_s;
	t_win		image_w;
	t_win		image_e;
	t_win		sprite;
	t_plr		plr;
	t_point		point;
	char		**map;
}				  t_all;

typedef struct	s_shot // структура для всего вместе
{
	unsigned int filesize;
	unsigned int reserved;
	unsigned int offset ;
	unsigned int headersize;
	unsigned int dimension_x;
	unsigned int dimension_y;
	unsigned short colorplanes;
	unsigned short bpp;
	unsigned int compression;
	unsigned int imgsize;
	unsigned int resolution_x;
	unsigned int resolution_y;
	unsigned int pltcolors;
	unsigned int impcolors;
}		t_shot;

#endif
