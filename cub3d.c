#include "mlx.h"
#include "cub3d.h"
#include "libft.h"
#include "errors.h"

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
	char    *dst;

	dst = data.addr + (y * data.line_len + x * (data.bpp / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_win all, int x, int y, int color)
{
	char    *dst;

	dst = all.addr + (y * all.line_len + x * (all.bpp / 8));
	*(unsigned int*)dst = color;
}

int	close_win(t_all	*all)
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

int fill_map_on_screen(t_all *all)
{
	int i;
	int j;

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
				if (all->map[i][j] == 'E')
					all->plr.dir = 0;
				else if (all->map[i][j] == 'S')
					all->plr.dir = M_PI_2;
				else if (all->map[i][j] == 'W')
					all->plr.dir = 3.1415;
				else if (all->map[i][j] == 'N')
					all->plr.dir = - M_PI_2;
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
	double temp_x;
	double temp_y;

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
	double temp_x;
	double temp_y;

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
	int	k;
	double	line;
	double	black;

	k = -1;
	line = SCALE * all->height / (hypot(all->plr.x - x, all->plr.y - y) * fabs(cos(all->plr.ray_start - all->plr.dir)));
	if (line >= all->height)
		line = 0;
	black = (all->height - line) / 2;
	while (++k < black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->floor_color);
	k--;
	while (++k < line + black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, my_mlx_get_color(all->image_e, (int)((y - (int)(y / SCALE) * SCALE) / SCALE * all->image_e.img_width), (k - black) / (line / all->image_e.img_height)));
	k--;
	while (++k < black * 2 + line)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->ceil_color);
}

void	put_image_w(t_all *all, int i, double x, double y)
{
	int	k;
	double	line;
	double	black;

	k = -1;
	line = SCALE * all->height / (hypot(all->plr.x - x, all->plr.y - y) * fabs(cos(all->plr.ray_start - all->plr.dir)));
	if (line >= all->height)
		line = 0;
	black = (all->height - line) / 2;
	while (++k < black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->floor_color);
	k--;
	while (++k < line + black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, my_mlx_get_color(all->image_w, (int)(all->image_w.img_width - (y - (int)(y / SCALE) * SCALE) / SCALE * all->image_w.img_width), (k - black) / (line / all->image_w.img_height)));
	k--;
	while (++k < black * 2 + line)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->ceil_color);
}

void	put_image_n(t_all *all, int i, double x, double y)
{
	int	k;
	double	line;
	double	black;

	k = -1;
	line = SCALE * all->height / (hypot(all->plr.x - x, all->plr.y - y) * fabs(cos(all->plr.ray_start - all->plr.dir)));
	if (line >= all->height)
		line = 0;
	black = (all->height - line) / 2;
	while (++k < black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->floor_color);
	k--;
	while (++k < line + black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k,  my_mlx_get_color(all->image_n, (int)((x - (int)(x / SCALE) * SCALE) / SCALE * all->image_n.img_width), (k - black) / (line / all->image_n.img_height)));
	k--;
	while (++k < black * 2 + line)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->ceil_color);
}

void	put_image_s(t_all *all, int i, double x, double y)
{
	int	k;
	double	line;
	double	black;

	k = -1;
	line = SCALE * all->height / (hypot(all->plr.x - x, all->plr.y - y) * fabs(cos(all->plr.ray_start - all->plr.dir)));
	if (line >= all->height)
		line = 0;
	black = (all->height - line) / 2;
	while (++k < black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->floor_color);
	k--;
	while (++k < line + black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, my_mlx_get_color(all->image_s, (int)(all->image_s.img_width - (x - (int)(x / SCALE) * SCALE) / SCALE * all->image_s.img_width), (k - black) / (line / all->image_s.img_height)));
	k--;
	while (++k < black * 2 + line)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, all->ceil_color);
}

void		find_line(t_all *all, double *x1, double *y1)
{
	double x2;
	double y2;
	double x3;
	double y3;

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
	int		k;
	unsigned int	color;
	double	tmp_x;
	double	tmp_y;
	double line;
	double black;
	int j;

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
	while (++k < black);
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
	k--;
	while (++k < black * 2 + line);
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
		if (all->point.v_flag == 1 && ((all->plr.ray_start >= - M_PI_2 && all->plr.ray_start <= M_PI_2) || (all->plr.ray_start <= - 3 * M_PI_2 && all->plr.ray_start >= - 2 * M_PI)))
			put_image_e(all, i, x, y);
		else if (all->point.v_flag == 1)
			put_image_w(all, i, x, y);
		else if (all->point.h_flag == 1 && ((all->plr.ray_start >= - M_PI && all->plr.ray_start <= 0) || (all->plr.ray_start >= M_PI && all->plr.ray_start <= 3 * M_PI_2)))
			put_image_n(all, i, x, y);
		else
			put_image_s(all, i, x, y);

}

void	cast_ray(t_all *all)
{
	double x;
	double y;
	int i;

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
		all->plr.ray_start = - atan((all->width / 2 - i + 1) /
				(sqrt(3) * (all->width / 2))) + all->plr.dir;
		cast_ray_set_def(&x, &y, all);
	}
}

void move_plr(int keycode, t_all *all)
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

int	key_hook(int keycode, t_all *all)
{
	/* printf("%d\n", keycode); */
	move_plr(keycode, all);
	if (all->plr.dir <= - 3 * M_PI_2)
		all->plr.dir += 2 * M_PI;
	if (all->plr.dir >= M_PI)
		all->plr.dir -= 2 * M_PI;
	if (keycode == 65307 || keycode == 53)
		close_win(all);
	mlx_destroy_image(all->win.mlx, all->win.img);
	all->win.img = mlx_new_image(all->win.mlx, all->width, all->height);
	all->win.addr = mlx_get_data_addr(all->win.img, &all->win.bpp, &all->win.line_len, &all->win.end);
	cast_ray(all);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
	return (1);
}

char	**parcer(int fd)
{
	char **map;
	char *line;
	int i;
	t_list *map_list;
	t_list *temp;

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

void screenshot_filler(t_shot *shot, t_all all)
{
	shot->filesize = 14 + 40 + all.width * all.height * 4;
	shot->reserved = 0;
	shot->offset = 14 + 40;
	shot->headersize = 40;
	shot->dimension_x = all.width;
	shot->dimension_y = all.height;
	shot->colorplanes = 1;
	shot->bpp = 32;
	shot->compression = 0;
	shot->imgsize = all.width * all.width * 4;
	shot->resolution_x = 2795;
	shot->resolution_y = 2795;
	shot->pltcolors = 0;
	shot->impcolors = 0;
}

void screenshot_header(int fd, t_all all)
{
	t_shot shot;

	screenshot_filler(&shot, all);
	write(fd, "BM", 2);
	write(fd, (char *)(&shot.filesize), sizeof(shot.filesize));
	write(fd, (char *)(&shot.reserved), sizeof(shot.reserved));
	write(fd, (char *)(&shot.offset), sizeof(shot.offset));

	write(fd, (char *)(&shot.headersize), sizeof(shot.headersize));
	write(fd, (char *)(&shot.dimension_x), sizeof(shot.dimension_x));
	write(fd, (char *)(&shot.dimension_y), sizeof(shot.dimension_y));
	write(fd, (char *)(&shot.colorplanes), sizeof(shot.colorplanes));
	write(fd, (char *)(&shot.bpp), sizeof(shot.bpp));
	write(fd, (char *)(&shot.compression), sizeof(shot.compression));
	write(fd, (char *)(&shot.imgsize), sizeof(shot.imgsize));
	write(fd, (char *)(&shot.resolution_x), sizeof(shot.resolution_x));
	write(fd, (char *)(&shot.resolution_y), sizeof(shot.resolution_y));
	write(fd, (char *)(&shot.pltcolors), sizeof(shot.pltcolors));
	write(fd, (char *)(&shot.impcolors), sizeof(shot.impcolors));
}

void screenshot_trgb(int fd, int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char t;

	t = 0;
	r = get_r(color) / 65536;
	g = get_g(color) / 256;
	b = get_b(color);
	write(fd, (char *)(&b), sizeof(b));
	write(fd, (char *)(&g), sizeof(g));
	write(fd, (char *)(&r), sizeof(r));
	write(fd, (char *)(&t), sizeof(t));
}

void screenshot(t_all all)
{
	int fd;
	int x;
	int y;
	int color;

	x = 0;
	y = all.height;
	fd = open("img.bmp", O_CREAT | O_RDWR | O_TRUNC);
	screenshot_header(fd, all);
	while (y - 1 >= 0)
	{
		x = 0;
		while (x < all.width)
		{
			color = my_mlx_get_color(all.win, x, y - 1);
			screenshot_trgb(fd, color);
			x++;
		}
		y--;
	}
	close(fd);
}

void fill_header(t_all *all)
{
	all->header.res = 0;
	all->header.no = 0;
	all->header.so = 0;
	all->header.we = 0;
	all->header.ea = 0;
	all->header.s = 0;
	all->header.f = 0;
	all->header.c = 0;
}

int strs_len(char **strs)
{
	int len;

	len = 0;
	if (strs != 0)
		while (strs[len] != 0)
			len++;
	return (len);
}

void free_strs(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs[i]);
	free(strs);
}

int check_header_dublicates(t_all all)
{
	if (all.header.res > 1)
		return (0);
	if (all.header.no > 1)
		return (0);
	if (all.header.so > 1)
		return (0);
	if (all.header.we > 1)
		return (0);
	if (all.header.ea > 1)
		return (0);
	if (all.header.s > 1)
		return (0);
	if (all.header.f > 1)
		return (0);
	if (all.header.c > 1)
		return (0);
	return (1);
}

char *check_header(t_all all)
{
	if (all.header.res != 1)
		return (CONF);
	if (all.header.no != 1)
		return (CONF);
	if (all.header.so != 1)
		return (CONF);
	if (all.header.we != 1)
		return (CONF);
	if (all.header.ea != 1)
		return (CONF);
	if (all.header.s != 1)
		return (CONF);
	if (all.header.f != 1)
		return (CONF);
	if (all.header.c != 1)
		return (CONF);
	return ("1");
}

char *check_fill_res(int i, t_all *all)
{
	int j;
	char **strs;
	int resx;
	int resy;

	j = 0;
	while (all->map[i][++j] != 0)
		if ((all->map[i][j] < '0' || all->map[i][j] > '9') && all->map[i][j] != ' ')
			return (RES);
	j = 0;
	strs = ft_split(all->map[i], ' ');
	if (strs_len(strs) != 3)
		return (RES);
	all->width = ft_atoi(strs[1]);
	all->height = ft_atoi(strs[2]);
	mlx_get_screen_size(all->win.mlx, &resx, &resy);
	if (all->width > resx)
		all->width = resx;
	if (all->height > resy)
		all->height = resy;
	if (all->width <= 0 || all->height <= 0)
		return (RES);
	free_strs(strs);
	all->header.res++;
	return ("1");
}

char *check_fill_no(int i, t_all *all)
{
	char **strs;
	int fd;

	strs = ft_split(all->map[i], ' ');
	if (strs_len(strs) != 2)
		return (NO);
	if ((ft_strrchr(strs[1], '.') == NULL) || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
		return (NO);
	all->image_n.path = ft_strdup(strs[1]);
	fd = open(all->image_n.path, O_RDONLY);
	if (fd == -1)
		return (PATH_NO);
	close (fd);
	if (all->image_n.path == NULL)
		return (NO);
	free_strs(strs);
	all->header.no++;
	close(fd);
	return ("1");
}

char *check_fill_so(int i, t_all *all)
{
	char **strs;
	int fd;

	strs = ft_split(all->map[i], ' ');
	if (strs_len(strs) != 2)
		return (SO);
	if ((ft_strrchr(strs[1], '.') == NULL) || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
		return (SO);
	all->image_s.path = ft_strdup(strs[1]);
	fd = open(all->image_s.path, O_RDONLY);
	if (fd == -1)
		return (PATH_SO);
	close (fd);
	if (all->image_s.path == NULL)
		return (SO);
	free_strs(strs);
	all->header.so++;
	close(fd);
	return ("1");
}

char *check_fill_we(int i, t_all *all)
{
	char **strs;
	int fd;

	strs = ft_split(all->map[i], ' ');
	if (strs_len(strs) != 2)
		return (WE);
	if ((ft_strrchr(strs[1], '.') == NULL) || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
		return (WE);
	all->image_w.path = ft_strdup(strs[1]);
	fd = open(all->image_w.path, O_RDONLY);
	if (fd == -1)
		return (PATH_WE);
	close (fd);
	if (all->image_w.path == NULL)
		return (WE);
	free_strs(strs);
	all->header.we++;
	close(fd);
	return ("1");
}

char *check_fill_ea(int i, t_all *all)
{
	char **strs;
	int fd;

	strs = ft_split(all->map[i], ' ');
	if (strs_len(strs) != 2)
		return (EA);
	if ((ft_strrchr(strs[1], '.') == NULL) || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
		return (EA);
	all->image_e.path = ft_strdup(strs[1]);
	fd = open(all->image_e.path, O_RDONLY);
	if (fd == -1)
		return (PATH_EA);
	close (fd);
	if (all->image_e.path == NULL)
		return (EA);
	free_strs(strs);
	all->header.ea++;
	close(fd);
	return ("1");
}

char *check_fill_s(int i, t_all *all)
{
	char **strs;
	int fd;

	strs = ft_split(all->map[i], ' ');
	if (strs_len(strs) != 2)
		return (S);
	if ((ft_strrchr(strs[1], '.') == NULL) || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
		return (S);
	all->sprite.path = ft_strdup(strs[1]);
	fd = open(all->sprite.path, O_RDONLY);
	if (fd == -1)
		return (PATH_S);
	close (fd);
	if (all->sprite.path == NULL)
		return (S);
	free_strs(strs);
	all->header.s++;
	close(fd);
	return ("1");
}

int check_one_num(char *str)
{
	char **strs;
	int num;

	strs = ft_split(str, ' ');
	if (strs_len(strs) != 1)
		return (-1);
	num = ft_atoi(strs[0]);
	free_strs(strs);
	return (num);
}

char *check_fill_f(int i, t_all *all)
{
	char **strs;
	char *str;
	int r;
	int g;
	int b;

	r = 0;
	while (all->map[i][++r] != 0)
		if ((all->map[i][r] < '0' || all->map[i][r] > '9') && all->map[i][r] != ' ' && all->map[i][r] != ',')
			return (FLOOR);
	str = all->map[i] + 1;
	strs = ft_split(str, ',');
	if (strs_len(strs) != 3)
		return (FLOOR);
	r = check_one_num(strs[0]);
	g = check_one_num(strs[1]);
	b = check_one_num(strs[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (FLOOR);
	all->floor_color = create_trgb(0, r, g, b);
	free_strs(strs);
	all->header.f++;
	return ("1");
}

char *check_fill_c(int i, t_all *all)
{
	char **strs;
	char *str;
	int r;
	int g;
	int b;

	r = 0;
	while (all->map[i][++r] != 0)
		if ((all->map[i][r] < '0' || all->map[i][r] > '9') && all->map[i][r] != ' ' && all->map[i][r] != ',')
			return (CEIL);
	str = all->map[i] + 1;
	strs = ft_split(str, ',');
	if (strs_len(strs) != 3)
		return (CEIL);
	r = check_one_num(strs[0]);
	g = check_one_num(strs[1]);
	b = check_one_num(strs[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (CEIL);
	all->ceil_color = create_trgb(0, r, g, b);
	free_strs(strs);
	all->header.c++;
	return ("1");
}

char *check_circuit(int i, int end, t_all all)
{
	int j;
	int start;

	j = 0;
	start = i;
	while (all.map[i] != 0)
	{
		j = 0;
		while (all.map[i][j] != 0)
		{
			if (all.map[i][j] == '0' || all.map[i][j] == '2' || all.map[i][j] == 'N' || all.map[i][j] == 'W' || all.map[i][j] == 'S' || all.map[i][j] == 'E')
			{
				if ((i == start) || (j == 0) || (j > (int)ft_strlen(all.map[i - 1])) || all.map[i - 1][j - 1] == ' ')
					return (BAD_CIRCUIT);
				if ((i == start) || (j > (int)ft_strlen(all.map[i - 1]) - 1) || all.map[i - 1][j] == ' ')
					return (BAD_CIRCUIT);
				if ((i == start) || (j > (int)ft_strlen(all.map[i - 1]) - 2) || all.map[i - 1][j + 1] == ' ')
					return (BAD_CIRCUIT);
				if ((j > (int)ft_strlen(all.map[i]) - 2) || all.map[i][j + 1] == ' ')
					return (BAD_CIRCUIT);
				if ((i == end) || (j > (int)ft_strlen(all.map[i + 1]) - 2) || all.map[i + 1][j + 1] == ' ')
					return (BAD_CIRCUIT);
				if ((i == end) || (j > (int)ft_strlen(all.map[i + 1]) - 1) || all.map[i + 1][j] == ' ')
					return (BAD_CIRCUIT);
				if ((i == end) || (j == 0) || (j > (int)ft_strlen(all.map[i + 1])) || all.map[i + 1][j - 1] == ' ')
					return (BAD_CIRCUIT);
				if ((j == 0) || (j > (int)ft_strlen(all.map[i])) || all.map[i][j - 1] == ' ')
					return (BAD_CIRCUIT);
			}
			j++;
		}
		i++;
	}
	return ("1");
}

char *check_player(int i, t_all all)
{
	int j;
	int count;

	count = 0;
	j = 0;
	while (all.map[i] != 0)
	{
		j = 0;
		while (all.map[i][j] != 0)
		{
			if (all.map[i][j] == 'N' || all.map[i][j] == 'W' || all.map[i][j] == 'S' || all.map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (PLAYER);
	return ("1");
}

char *check_symbols(int i, t_all all)
{
	int j;
	int temp_i;

	temp_i = i;
	j = 0;
	while (all.map[i] != 0)
	{
		j = 0;
		if (ft_strlen(all.map[i]) == 0)
			return (MAP_EMPTY_LINE);
		while (all.map[i][j])
		{
			if (all.map[i][j] != ' ' && all.map[i][j] != '1' && all.map[i][j] != '0' && all.map[i][j] != 'N' && all.map[i][j] != 'W' && all.map[i][j] != 'S' && all.map[i][j] != 'E' && all.map[i][j] != '2')
				return (MAP_WRONG_SYMBOLS);
			j++;
		}
		i++;
	}
	if (check_circuit(temp_i, i - 1, all)[0] != '1')
		return (BAD_CIRCUIT);
	return ("1");
}

char *check_map(int i, t_all all)
{
	if (check_player(i, all)[0] != '1')
		return (check_player(i, all));
	if (check_symbols(i, all)[0] != '1')
		return (check_symbols(i, all));
	return ("1");
}

char *check_ident(int *i, t_all *all)
{
	char *answer;

	if (ft_strlen(all->map[*i]) == 0)
		return ("1");
	else if (ft_strncmp(all->map[*i], "R ", 2) == 0)
		answer = check_fill_res(*i, all);
	else if (ft_strncmp(all->map[*i], "NO ", 3) == 0)
		answer = check_fill_no(*i, all);
	else if (ft_strncmp(all->map[*i], "SO ", 3) == 0)
		answer = check_fill_so(*i, all);
	else if (ft_strncmp(all->map[*i], "WE ", 3) == 0)
		answer = check_fill_we(*i, all);
	else if (ft_strncmp(all->map[*i], "EA ", 3) == 0)
		answer = check_fill_ea(*i, all);
	else if (ft_strncmp(all->map[*i], "S ", 2) == 0)
		answer = check_fill_s(*i, all);
	else if (ft_strncmp(all->map[*i], "F ", 2) == 0)
		answer = check_fill_f(*i, all);
	else if (ft_strncmp(all->map[*i], "C ", 2) == 0)
		answer = check_fill_c(*i, all);
	else
		return ("0");
	if (answer[0] != '1')
		return (answer);
	return ("1");
}

int check_empty_line(int i, t_all all)
{
	int j;

	j = 0;
	while (all.map[i][j])
	{
		if (all.map[i][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int check_line(int i, t_all all)
{
	int j;

	j = 0;
	while (all.map[i][j] != 0)
	{
		if (all.map[i][j] != ' ' && all.map[i][j] != '1' && all.map[i][j] != '0' && all.map[i][j] != 'N' && all.map[i][j] != 'W' && all.map[i][j] != 'S' && all.map[i][j] != 'E' && all.map[i][j] != '2')
			return (0);
		j++;
	}
	return (1);
}

char *check_cub(t_all *all)
{
	int i;

	fill_header(all);
	i = 0;
	if (all->map[i] == 0)
		return (EMPTY_FILE);
	while (check_ident(&i, all)[0] == '1')
	{
		if (all->map[i] == 0)
			break;
		i++;
	}
	if (all->map[i] == 0 && check_header(*all)[0] != '1') // нет карты, но что-то с количеством идентификаторов
		return (check_header(*all));
	if (check_ident(&i, all)[0] == '1') // с идентификаторами все норм, но нет карты
		return (NO_MAP);
	if (check_empty_line(i, *all) == 0) // строка из пробелов
		return (WRONG_LINE);
	if (check_ident(&i, all)[0] != '0' && check_ident(&i, all)[0] != '1') // ошибка идентификатора
		return (check_ident(&i, all));	
	if (check_ident(&i, all)[0] == '0' && check_header_dublicates(*all) == 1 && check_header(*all)[0] != '1' && check_line(i, *all) == 0) // рандом строка, в идентификаторах нет дубликатов и они не все есть
		return (WRONG_LINE);
	if (check_header(*all)[0] != '1') //
		return (check_header(*all));
	if (check_map(i, *all)[0] != '1') // чекаю карту
		return (check_map(i, *all));
	return ("1");
}

int main(int argc, char **argv)
{
	t_all	all;
	int fd;
	char *checker;

	if (argc == 1)
	{
		printf("Error\nMap not specified");
		return (0);
	}
	if (argc > 3)
	{
		printf("Error\nMore than 2 arguments");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	all.map = parcer(fd);
	all.win.mlx = mlx_init();
	checker = check_cub(&all);
	if (checker[0] != '1')
	{
		close(fd);
		printf("Error\n%s", checker);
		return (0);
	}
	else
		printf("Всё норм, не забудь убрать!\n");

	all.win.win = mlx_new_window(all.win.mlx, all.width, all.height, "cub3d");
	all.win.img = mlx_new_image(all.win.mlx, all.width, all.height);
	all.win.addr = mlx_get_data_addr(all.win.img, &all.win.bpp, &all.win.line_len, &all.win.end);

	all.image_e.img = mlx_xpm_file_to_image(all.win.mlx, all.image_e.path, &all.image_e.img_width, &all.image_e.img_height);
	all.image_e.addr = mlx_get_data_addr(all.image_e.img, &all.image_e.bpp, &all.image_e.line_len, &all.image_e.end);

	all.image_s.img = mlx_xpm_file_to_image(all.win.mlx, all.image_s.path, &all.image_s.img_width, &all.image_s.img_height);
	all.image_s.addr = mlx_get_data_addr(all.image_s.img, &all.image_s.bpp, &all.image_s.line_len, &all.image_s.end);

	all.image_n.img = mlx_xpm_file_to_image(all.win.mlx, all.image_n.path, &all.image_n.img_width, &all.image_n.img_height);
	all.image_n.addr = mlx_get_data_addr(all.image_n.img, &all.image_n.bpp, &all.image_n.line_len, &all.image_n.end);

	all.image_w.img = mlx_xpm_file_to_image(all.win.mlx, all.image_w.path, &all.image_w.img_width, &all.image_w.img_height);
	all.image_w.addr = mlx_get_data_addr(all.image_w.img, &all.image_w.bpp, &all.image_w.line_len, &all.image_w.end);

	all.sprite.img = mlx_xpm_file_to_image(all.win.mlx, all.sprite.path, &all.sprite.img_width, &all.sprite.img_height);
	all.sprite.addr = mlx_get_data_addr(all.sprite.img, &all.sprite.bpp, &all.sprite.line_len, &all.sprite.end);
	fill_map_on_screen(&all);
	cast_ray(&all);
	mlx_put_image_to_window(all.win.mlx, all.win.win, all.win.img, 0, 0);
	if ((argc == 3) && ft_strncmp(argv[2], "--save", 7) == 0)
	{
		close(fd);
		screenshot(all);
		close_win(&all);
		return (1);
	}
	mlx_hook(all.win.win, 17, 0L, close_win, &all);
	mlx_hook(all.win.win, 2, 1L<<0, key_hook, &all);
	mlx_loop(all.win.mlx);
	return (1);
}
