/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:02:15 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/24 18:57:39 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define SCALE 62

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "../headers/mlx.h"
# include "../libft/libft.h"
# include "../headers/errors.h"
# include "../get_next_line/get_next_line.h"

typedef struct		s_win
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*addr;
	char			*path;
	int				line_len;
	int				bpp;
	int				end;
	int				img_width;
	int				img_height;
}					t_win;

typedef struct		s_point
{
	double			v_x;
	double			v_y;
	double			v_len;
	int				v_flag;
	double			h_x;
	double			h_y;
	double			h_len;
	int				h_flag;

}					t_point;

typedef struct		s_plr
{
	double			x;
	double			y;
	double			dir;
	double			ray_start;
	double			ray_end;
}					t_plr;

typedef struct		s_header
{
	int				res;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				s;
	int				f;
	int				c;
}					t_header;

typedef struct		s_all
{
	t_win			win;
	t_win			image_n;
	t_win			image_s;
	t_win			image_w;
	t_win			image_e;
	t_win			sprite;
	t_plr			plr;
	t_point			point;
	t_header		header;
	double			line;
	unsigned int	color;
	int				ceil_color;
	int				floor_color;
	int				width;
	int				height;
	char			**map;
}					t_all;

typedef struct		s_shot
{
	unsigned int	filesize;
	unsigned int	reserved;
	unsigned int	offset;
	unsigned int	headersize;
	unsigned int	dimension_x;
	unsigned int	dimension_y;
	unsigned short	colorplanes;
	unsigned short	bpp;
	unsigned int	compression;
	unsigned int	imgsize;
	unsigned int	resolution_x;
	unsigned int	resolution_y;
	unsigned int	pltcolors;
	unsigned int	impcolors;
}					t_shot;

int					get_r(int trgb);
int					get_g(int trgb);
int					get_b(int trgb);
int					create_trgb(int t, int r, int g, int b);
unsigned int		my_mlx_get_color(t_win data, int x, int y);
void				my_mlx_pixel_put(t_win all, int x, int y, int color);
int					close_win(t_all *all);
void				choose_dir(t_all *all, int i, int j);
int					fill_map_on_screen(t_all *all);
void				horizont_point(t_all *all);
void				vertical_point(t_all *all);
void				put_image_e(t_all *all, int i, double x, double y);
void				put_image_w(t_all *all, int i, double x, double y);
void				put_image_n(t_all *all, int i, double x, double y);
void				put_image_s(t_all *all, int i, double x, double y);
void				tan_exp_f(t_all *all, double *x1, double *x2);
void				tan_exp_s(t_all *all, double *y1, double *y2);
void				dot_x_y(t_all *all, double *x3, double *y3);
void				find_line(t_all *all, double *x1, double *y1);
int					borders_cut(t_all *all, double tmp_x, double tmp_y);
void				line_len(t_all *all, double *tmp_x, double *tmp_y);
int					color_f_part(t_all *all, int k, double tmp_x, double tmp_y);
int					color_s_part(t_all *all, int k, double tmp_x, double tmp_y);
void				put_sprite(t_all *all, int i, double x, double y);
void				cast_ray_set_def(double *x, double *y, t_all *all);
void				cast_ray_next(double *x, double *y, t_all *all);
void				select_texture(t_all *all, int i, double x, double y);
void				cast_ray(t_all *all);
void				move_plr(int keycode, t_all *all);
int					key_hook(int keycode, t_all *all);
char				**parcer(int fd);
void				screenshot_filler(t_shot *shot, t_all all);
void				screenshot_header(int fd, t_all all);
void				screenshot_trgb(int fd, int color);
int					screenshot(t_all all);
void				fill_header(t_all *all);
int					strs_len(char **strs);
void				free_strs(char **strs);
int					check_header_dublicates(t_all all);
char				*check_header(t_all all);
char				*check_fill_res(int i, t_all *all, int argc);
char				*check_fill_no(int i, t_all *all);
char				*check_fill_so(int i, t_all *all);
char				*check_fill_we(int i, t_all *all);
char				*check_fill_ea(int i, t_all *all);
char				*check_fill_s(int i, t_all *all);
int					check_one_num(char *str);
char				*check_fill_f(int i, t_all *all);
char				*check_fill_c(int i, t_all *all);
char				*check_circuit_start(t_all all, int i, int j, int start);
char				*check_circuit_end(t_all all, int i, int j, int end);
char				*check_circuit(int i, int end, t_all all);
char				*check_player(int i, t_all all);
char				*check_symbols(int i, t_all all);
char				*check_map(int i, t_all all);
char				*check_ident(int *i, t_all *all, int argc);
int					check_empty_line(int i, t_all all);
int					check_line(int i, t_all all);
char				*check_cub(t_all *all, int a);
int					check_argc(int argc, char **argv, int *fd);
int					exit_after_check_cub(t_all *all, int argc, int fd);
int					xpm_to_images(t_all *all);
int					quantity_comma(char *str);
int					do_images(t_all *all);
int					do_check_screenshot(int argc, char **argv, t_all *all,
					int fd);
#endif
