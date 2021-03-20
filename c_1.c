#include "cub3d.h"

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

unsigned int	my_mlx_get_color(t_win data, int x, int y)
{
	char	*dst;

	dst = data.addr + (y * data.line_len + x * (data.bpp / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_win all, int x, int y, int color)
{
	char	*dst;

	dst = all.addr + (y * all.line_len + x * (all.bpp / 8));
	*(unsigned int*)dst = color;
}

int	close_win(t_all *all)
{
	free(all->image_n.path);
	free(all->image_e.path);
	free(all->image_w.path);
	free(all->image_s.path);
	free(all->sprite.path);
	mlx_destroy_image(all->win.mlx, all->image_n.img);
	mlx_destroy_image(all->win.mlx, all->image_e.img);
	mlx_destroy_image(all->win.mlx, all->image_w.img);
	mlx_destroy_image(all->win.mlx, all->image_s.img);
	mlx_destroy_image(all->win.mlx, all->sprite.img);
	mlx_clear_window(all->win.mlx, all->win.win);
	mlx_destroy_window(all->win.mlx, all->win.win);
	exit(1);
	return (1);
}

void	choose_dir(t_all *all, int i, int j)
{
	if (all->map[i][j] == 'E')
		all->plr.dir = 0;
	else if (all->map[i][j] == 'S')
		all->plr.dir = M_PI_2;
	else if (all->map[i][j] == 'W')
		all->plr.dir = 3.1415;
	else if (all->map[i][j] == 'N')
		all->plr.dir = - M_PI_2;
}

int		fill_map_on_screen(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == 'N' || all->map[i][j] == 'W' || all->map[i][j] == 'S' || all->map[i][j] == 'E')
			{
				all->plr.x = j * SCALE + SCALE / 2;
				all->plr.y = i * SCALE + SCALE / 2;
				choose_dir(all, i, j);
				all->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	horizont_point(t_all *all)
{
	double	temp_x;
	double	temp_y;

	temp_x = all->point.h_x;
	temp_y = all->point.h_y;
	if ((all->plr.ray_start >= - M_PI && all->plr.ray_start <= 0) || (all->plr.ray_start >= M_PI && all->plr.ray_start <= 3 * M_PI_2))
		all->point.h_y = (int)(temp_y / SCALE) * SCALE - 0.00009;
	else
		all->point.h_y = (int)(temp_y / SCALE) * SCALE + SCALE;
	all->point.h_x = temp_x - (temp_y - all->point.h_y) / tan(all->plr.ray_start);
	all->point.h_len =  hypot(all->plr.x - all->point.h_x, all->plr.y - all->point.h_y);
}

void	vertical_point(t_all *all)
{
	double	temp_x;
	double	temp_y;

	temp_x = all->point.v_x;
	temp_y = all->point.v_y;
	if ((all->plr.ray_start >= - M_PI_2 && all->plr.ray_start <= M_PI_2) || (all->plr.ray_start <= - 3 * M_PI_2 && all->plr.ray_start >= - 2 * M_PI))
		all->point.v_x = (int)(temp_x / SCALE) * SCALE + SCALE;
	else
		all->point.v_x = (int)(temp_x / SCALE) * SCALE - 0.00009;
	all->point.v_y = temp_y - (temp_x - all->point.v_x) * tan(all->plr.ray_start);
	all->point.v_len =  hypot(all->plr.x - all->point.v_x, all->plr.y - all->point.v_y);
}

void	put_image_e(t_all *all, int i, double x, double y)
{
	int		k;
	double	line;
	double	black;

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
						(int)((y - (int)(y / SCALE) * SCALE) / SCALE *
							all->image_e.img_width), (k - black) /
						(line / all->image_e.img_height)));
	k--;
	while (++k < black * 2 + line)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->ceil_color);
}

void	put_image_w(t_all *all, int i, double x, double y)
{
	int		k;
	double	line;
	double	black;

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
							SCALE * all->image_w.img_width), (k - black) /
						(line / all->image_w.img_height)));
	k--;
	while (++k < black * 2 + line)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->ceil_color);
}

void	put_image_n(t_all *all, int i, double x, double y)
{
	int		k;
	double	line;
	double	black;

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
			my_mlx_pixel_put(all->win, i, k,  my_mlx_get_color(all->image_n,
						(int)((x - (int)(x / SCALE) * SCALE) / SCALE *
							all->image_n.img_width), (k - black) /
						(line / all->image_n.img_height)));
	k--;
	while (++k < black * 2 + line)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->ceil_color);
}

void	put_image_s(t_all *all, int i, double x, double y)
{
	int		k;
	double	line;
	double	black;

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

void	find_line(t_all *all, double *x1, double *y1)
{
	double	x2;
	double	y2;
	double	x3;
	double	y3;

	x2 = *x1 + tan(all->plr.dir) * SCALE;
	if ((all->plr.dir >= 0 && all->plr.dir <= M_PI_2) || (all->plr.dir >= - M_PI && all->plr.dir <= - M_PI_2))
		x2 = *x1 - tan(all->plr.dir) * SCALE;
	y2 = *y1 + 1 / tan(all->plr.dir) * SCALE;
	if (all->plr.dir == 0 || all->plr.dir == - 3.1415 || all->plr.dir == 3.1415)
		y2 = *y1 + SCALE;
	x3 = all->plr.x + cos(all->plr.ray_start) * SCALE;
	y3 = all->plr.y + sin(all->plr.ray_start) * SCALE;
	if ((int)((((*y1 - y2) * (all->plr.x * y3 - x3 * all->plr.y) - (all->plr.y - y3) * (*x1 * y2 - x2 * *y1)) / ((all->plr.y - y3) * (x2 - *x1) - (*y1 - y2) * (x3 - all->plr.x))) / SCALE) == (int)(*y1 / SCALE))
		*y1 = ((*y1 - y2) * (all->plr.x * y3 - x3 * all->plr.y) - (all->plr.y - y3) * (*x1 * y2 - x2 * *y1)) / ((all->plr.y - y3) * (x2 - *x1) - (*y1 - y2) * (x3 - all->plr.x));
	else
		*y1 = -1;
	if ((int)((- ((x3 - all->plr.x) / (all->plr.y - y3)) * *y1 - ((all->plr.x * y3 - x3 * all->plr.y) / (all->plr.y - y3))) / SCALE) == (int)(*x1 / SCALE))
		*x1 = - ((x3 - all->plr.x) / (all->plr.y - y3)) * *y1 - ((all->plr.x * y3 - x3 * all->plr.y) / (all->plr.y - y3));
	else if ((all->plr.y - y3) == 0)
		*x1 = *x1;
	else
		*x1 = -1;
}

void	put_sprite(t_all *all, int i, double x, double y)
{
	int				k;
	unsigned int	color;
	double			tmp_x;
	double			tmp_y;
	double			line;
	double			black;
	int				j;

	k = -1;
	j = 0;
	tmp_x = (int)(x / SCALE) * SCALE + SCALE / 2;
	tmp_y = (int)(y / SCALE) * SCALE + SCALE / 2;
	line = SCALE * all->height / (hypot(all->plr.x - tmp_x, all->plr.y - tmp_y) * ((tmp_x - all->plr.x) * (cos(all->plr.dir) * SCALE) + (tmp_y - all->plr.y) * (sin(all->plr.dir) * SCALE)) / (hypot(tmp_x - all->plr.x, tmp_y - all->plr.y) * hypot(cos(all->plr.dir) * SCALE, sin(all->plr.dir) * SCALE)));
	find_line(all, &tmp_x, &tmp_y);
	if (line >= all->height)
		line = 0;
	black = (all->height - line) / 2;
	if (all->plr.dir >= - M_PI_4 && all->plr.dir <= M_PI_4 && (int)(((tmp_y - (int)(tmp_y / SCALE) * SCALE) - SCALE * (1 - fabs(cos(all->plr.dir)))) / fabs(cos(all->plr.dir)) / SCALE * all->sprite.img_width) < 0)
		return;
	else if (((all->plr.dir <= - 3 * M_PI_4 && all->plr.dir >= - 5 * M_PI_4) || (all->plr.dir <= M_PI && all->plr.dir >= 3 * M_PI_4)) && (int)(((tmp_y - (int)(tmp_y / SCALE) * SCALE) - SCALE * (1 - fabs(cos(all->plr.dir)))) / fabs(cos(all->plr.dir)) / SCALE * all->sprite.img_width) - 1 < 0)
		return;
	else if (all->plr.dir >= - 3 * M_PI_4 && all->plr.dir <= - M_PI_4 && (int)(((tmp_x - (int)(tmp_x / SCALE) * SCALE) - SCALE * (1 - fabs(sin(all->plr.dir)))) / fabs(sin(all->plr.dir)) / SCALE * all->sprite.img_width) < 0)
		return;
	else if (((all->plr.dir >= - 3 * M_PI_2 && all->plr.dir <= - 5 * M_PI_4) || (all->plr.dir >= M_PI_4 && all->plr.dir <= 3 * M_PI_4)) && (int)(((tmp_x - (int)(tmp_x / SCALE) * SCALE) - SCALE * (1 - fabs(sin(all->plr.dir)))) / fabs(sin(all->plr.dir)) / SCALE * all->sprite.img_width) - 1 < 0)
		return;
	while (k < black)
		k++;
	k--;
	while (++k < line + black)
	{
		if (k >= j)
		{
			if (tmp_y != -1 && tmp_x != -1 && all->plr.dir >= - M_PI_4 && all->plr.dir <= M_PI_4)
				color = my_mlx_get_color(all->sprite, (int)(((tmp_y - (int)(tmp_y / SCALE) * SCALE) - SCALE * (1 - fabs(cos(all->plr.dir)))) / fabs(cos(all->plr.dir)) / SCALE * all->sprite.img_width), (k - black) / (line / all->sprite.img_height));
			else if (tmp_y != -1 && tmp_x != -1 && ((all->plr.dir <= - 3 * M_PI_4 && all->plr.dir >= - 5 * M_PI_4) || (all->plr.dir <= M_PI && all->plr.dir >= 3 * M_PI_4)))
				color = my_mlx_get_color(all->sprite, (int)(all->sprite.img_width - ((tmp_y - (int)(tmp_y / SCALE) * SCALE) - SCALE * (1 - fabs(cos(all->plr.dir)))) / fabs(cos(all->plr.dir)) / SCALE * all->sprite.img_width), (k - black) / (line / all->sprite.img_height));
			else if (tmp_y != -1 && tmp_x != -1 && all->plr.dir >= - 3 * M_PI_4 && all->plr.dir <= - M_PI_4)
				color = my_mlx_get_color(all->sprite, (int)(((tmp_x - (int)(tmp_x / SCALE) * SCALE) - SCALE * (1 - fabs(sin(all->plr.dir)))) / fabs(sin(all->plr.dir)) / SCALE * all->sprite.img_width), (k - black) / (line / all->sprite.img_height));
			else if (tmp_y != -1 && tmp_x != -1)
				color = my_mlx_get_color(all->sprite, (int)(all->sprite.img_width - ((tmp_x - (int)(tmp_x / SCALE) * SCALE) - SCALE * (1 - fabs(sin(all->plr.dir)))) / fabs(sin(all->plr.dir)) / SCALE * all->sprite.img_width), (k - black) / (line / all->sprite.img_height));
			j = k + line / all->sprite.img_height;
		}
		if (color != 4278190080 && tmp_y != -1 && tmp_y != -1 && my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, color);
	}
}

void	cast_ray_set_def(double *x, double *y, t_all *all)
{
	all->point.h_x = all->plr.x;
	all->point.h_y = all->plr.y;
	all->point.v_x = all->plr.x;
	all->point.v_y = all->plr.y;
	*x = all->plr.x;
	*y = all->plr.y;
}

void	cast_ray_next(double *x, double *y, t_all *all)
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

void	select_texture(t_all *all, int i, int x, int y)
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

void	cast_ray(t_all *all)
{
	double	x;
	double	y;
	int		i;

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

void	move_plr(int keycode, t_all *all)
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

int		key_hook(int keycode, t_all *all)
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

char	**parcer(int fd)
{
	char	**map;
	char	*line;
	int		i;
	t_list	*map_list;
	t_list	*temp;

	map_list = NULL;
	while (get_next_line(fd, &line))
		ft_lstadd_back(&map_list, ft_lstnew(line));
	ft_lstadd_back(&map_list, ft_lstnew(line));
	map = ft_calloc(ft_lstsize(map_list) + 1, sizeof(char *));
	i = 0;
	while (map_list)
	{
		map[i] = map_list->content;
		temp = map_list;
		map_list = map_list->next;
		free(temp);
		i++;
	}
	free(map[i - 1]);
	map[i - 1] = NULL;
	return (map);
}
