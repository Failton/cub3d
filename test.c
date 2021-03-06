#include "mlx.h"
#include "cub3d.h"
#include "libft.h"


int	width = 900;
int	height = 600;
t_all	all;

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

int fill_map_on_screen(t_all *all)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;		
	while (all->map[i])
	{
		x = 0;
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == 'N')
			{
				all->plr.x = x + SCALE / 2;
				all->plr.y = y + SCALE / 2;
				all->plr.dir = 0;
				all->map[i][j] = '0';
			}
			x += SCALE;
			j++;
		}
		y += SCALE;
		i++;
	}
	return (1);
}

void	horizont_point(t_all *all, t_point *point)	
{
	double temp_x;
	double temp_y;

	temp_x = point->h_x;
	temp_y = point->h_y;
	if ((all->plr.ray_start >= - M_PI && all->plr.ray_start <= 0) || (all->plr.ray_start >= M_PI && all->plr.ray_start <= 3 * M_PI_2))
		point->h_y = (int)(temp_y / SCALE) * SCALE - 0.00009;
	else
		point->h_y = (int)(temp_y / SCALE) * SCALE + SCALE;
	point->h_x = temp_x - (temp_y - point->h_y) / tan(all->plr.ray_start);
	point->h_len =  hypot(all->plr.x - point->h_x, all->plr.y - point->h_y);
}

void	vertical_point(t_all *all, t_point *point)	
{
	double temp_x;
	double temp_y;

	temp_x = point->v_x;
	temp_y = point->v_y;
	if ((all->plr.ray_start >= - M_PI_2 && all->plr.ray_start <= M_PI_2) || (all->plr.ray_start <= - 3 * M_PI_2 && all->plr.ray_start >= - 2 * M_PI))
		point->v_x = (int)(temp_x / SCALE) * SCALE + SCALE;
	else
		point->v_x = (int)(temp_x / SCALE) * SCALE - 0.00009;
	point->v_y = temp_y - (temp_x - point->v_x) * tan(all->plr.ray_start);
	point->v_len =  hypot(all->plr.x - point->v_x, all->plr.y - point->v_y);
}

void	put_image_e(t_all *all, int i, double x, double y)
{
	int	k;
	double	line;
	double	black;

	k = -1;
	line = SCALE * height / (hypot(all->plr.x - x, all->plr.y - y) * fabs(cos(all->plr.ray_start - all->plr.dir)));
	if (line >= height)
		line = 0;
	black = (height - line) / 2;
	while (++k < black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00000000);
	k--;
	while (++k < line + black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, my_mlx_get_color(all->image_e, (int)((y - (int)(y / SCALE) * SCALE) / SCALE * all->image_e.img_width), (k - black) / (line / all->image_e.img_height)));
	k--;
	while (++k < black * 2 + line)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00665E4F);
}

void	put_image_w(t_all *all, int i, double x, double y)
{
	int	k;
	double	line;
	double	black;

	k = -1;
	line = SCALE * height / (hypot(all->plr.x - x, all->plr.y - y) * fabs(cos(all->plr.ray_start - all->plr.dir)));
	if (line >= height)
		line = 0;
	black = (height - line) / 2;
	while (++k < black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00000000);
	k--;
	while (++k < line + black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, my_mlx_get_color(all->image_w, (int)(all->image_w.img_width - (y - (int)(y / SCALE) * SCALE) / SCALE * all->image_w.img_width), (k - black) / (line / all->image_w.img_height)));
	k--;
	while (++k < black * 2 + line)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00665E4F);
}

void	put_image_n(t_all *all, int i, double x, double y)
{
	int	k;
	double	line;
	double	black;

	k = -1;
	line = SCALE * height / (hypot(all->plr.x - x, all->plr.y - y) * fabs(cos(all->plr.ray_start - all->plr.dir)));
	if (line >= height)
		line = 0;
	black = (height - line) / 2;
	while (++k < black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00000000);
	k--;
	while (++k < line + black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k,  my_mlx_get_color(all->image_n, (int)((x - (int)(x / SCALE) * SCALE) / SCALE * all->image_n.img_width), (k - black) / (line / all->image_n.img_height)));
	k--;
	while (++k < black * 2 + line)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00665E4F);
}

void	put_image_s(t_all *all, int i, double x, double y)
{
	int	k;
	double	line;
	double	black;

	k = -1;
	line = SCALE * height / (hypot(all->plr.x - x, all->plr.y - y) * fabs(cos(all->plr.ray_start - all->plr.dir)));
	if (line >= height)
		line = 0;
	black = (height - line) / 2;
	while (++k < black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00000000);
	k--;
	while (++k < line + black)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, my_mlx_get_color(all->image_s, (int)(all->image_s.img_width - (x - (int)(x / SCALE) * SCALE) / SCALE * all->image_s.img_width), (k - black) / (line / all->image_s.img_height)));
	k--;
	while (++k < black * 2 + line)
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00665E4F);
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
	line = SCALE * height / (hypot(all->plr.x - tmp_x, all->plr.y - tmp_y) * ((tmp_x - all->plr.x) * (cos(all->plr.dir) * SCALE) + (tmp_y - all->plr.y) * (sin(all->plr.dir) * SCALE)) / (hypot(tmp_x - all->plr.x, tmp_y - all->plr.y) * hypot(cos(all->plr.dir) * SCALE, sin(all->plr.dir) * SCALE)));
	find_line(all, &tmp_x, &tmp_y);
	if (line >= height)
		line = 0;
	black = (height - line) / 2;
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

void	cast_ray_set_def(t_point *point, double *x, double *y, t_all *all)
{
	point->h_x = all->plr.x;
	point->h_y = all->plr.y;
	point->v_x = all->plr.x;
	point->v_y = all->plr.y;
	*x = all->plr.x;
	*y = all->plr.y;
}

void	cast_ray_next(t_point *point, double *x, double *y, t_all *all)
{
	if (point->h_len < point->v_len)
	{
		*x = point->h_x;
		*y = point->h_y;
		point->h_flag = 1;
		point->v_flag = 0;
		horizont_point(all, point);
	}
	else
	{
		*x = point->v_x;
		*y = point->v_y;
		point->h_flag = 0;
		point->v_flag = 1;
		vertical_point(all, point);
	}

}

void	cast_ray(t_all *all)
{
	t_point point;
	double x;
	double y;
	int i;

	i = 0;
	all->plr.ray_end = all->plr.dir + M_PI / 6;
	all->plr.ray_start = all->plr.dir - M_PI / 6;
	cast_ray_set_def(&point, &x, &y, all);
	while (all->plr.ray_start <= all->plr.ray_end && i < width)
	{
		horizont_point(all, &point);
		vertical_point(all, &point);
		point.h_flag = 0;
		point.v_flag = 0;
		while (all->map[(int)(y / SCALE)][(int)(x / SCALE)] != '1')
		{
			if (all->map[(int)(y / SCALE)][(int)(x / SCALE)] == '2')
				put_sprite(all, i, x, y);
			cast_ray_next(&point, &x, &y, all);
		}
		if (point.v_flag == 1 && ((all->plr.ray_start >= - M_PI_2 && all->plr.ray_start <= M_PI_2) || (all->plr.ray_start <= - 3 * M_PI_2 && all->plr.ray_start >= - 2 * M_PI)))
			put_image_e(all, i, x, y);
		else if (point.v_flag == 1)
			put_image_w(all, i, x, y);
		else if (point.h_flag == 1 && ((all->plr.ray_start >= - M_PI && all->plr.ray_start <= 0) || (all->plr.ray_start >= M_PI && all->plr.ray_start <= 3 * M_PI_2)))
			put_image_n(all, i, x, y);
		else
			put_image_s(all, i, x, y);
		i++;
		all->plr.ray_start = - atan((width / 2 - i) / (sqrt(3) * (width / 2))) + all->plr.dir;
		cast_ray_set_def(&point, &x, &y, all);
	}
}

int	key_hook(int keycode, t_all *all)
{
	/* printf("%d\n", keycode); */
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
	if (keycode == 123 || keycode == 65361)
	{
		all->plr.x += sin(all->plr.dir) * 0.4 * SCALE;
		all->plr.y -= cos(all->plr.dir) * 0.4 * SCALE;
	}
	if (keycode == 124 || keycode == 65363)
	{
		all->plr.x -= sin(all->plr.dir) * 0.4 * SCALE;
		all->plr.y += cos(all->plr.dir) * 0.4 * SCALE;
	}
	if (keycode == 2 || keycode == 100)
		all->plr.dir += 0.15;
	if (keycode == 0 || keycode == 97)
		all->plr.dir -= 0.15;
	if (all->plr.dir <= - 3 * M_PI_2)
		all->plr.dir += 2 * M_PI;
	if (all->plr.dir >= M_PI)
		all->plr.dir -= 2 * M_PI;
	if (keycode == 65307)
		exit(1);
	mlx_destroy_image(all->win.mlx, all->win.img);
	all->win.img = mlx_new_image(all->win.mlx, width, height);
	all->win.addr = mlx_get_data_addr(all->win.img, &all->win.bpp, &all->win.line_len, &all->win.end);
	cast_ray(all);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
	return (1);
}

int	close_win(int keycode, t_all *all)
{
	(void)keycode;
	(void)all;

	exit(1);
	return (1);
}

char	**parcer(int fd)
{
	char **map;
	char *line;
	int i;
	t_list *map_list;

	map_list = NULL;
	while (get_next_line(fd, &line))
		ft_lstadd_back(&map_list, ft_lstnew(line));
	ft_lstadd_back(&map_list, ft_lstnew(line));
	map = ft_calloc(ft_lstsize(map_list) + 1, sizeof(char *));
	i = 0;
	while (map_list)
	{
		map[i] = map_list->content;
		map_list = map_list->next;
		i++;
	}
	return (map);
}

void screenshot_filler(t_shot *shot)
{
	shot->filesize = 14 + 40 + width*height*4;
	shot->reserved = 0;
	shot->offset = 14 + 40;
	shot->headersize = 40;
	shot->dimension_x = width;
	shot->dimension_y = height;
	shot->colorplanes = 1;
	shot->bpp = 32;
	shot->compression = 0;
	shot->imgsize = width * width * 4;
	shot->resolution_x = 2795;
	shot->resolution_y = 2795;
	shot->pltcolors = 0;
	shot->impcolors = 0;
}

void screenshot_header(int fd)
{
	t_shot shot;

	screenshot_filler(&shot);
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

void screenshot()
{
	int fd;
	int x;
	int y;
	int color;

	x = 0;
	y = height;
	fd = open("img.bmp", O_CREAT | O_RDWR | O_TRUNC);
	screenshot_header(fd);
	while (y - 1 >= 0)
	{
		x = 0;
		while (x < width)
		{
			color = my_mlx_get_color(all.win, x, y - 1);
			screenshot_trgb(fd, color);
			x++;
		}
		y--;
	}
}

int main(int argc, char **argv)
{
	char    *e_path = "./image_e.xpm";
	char	*s_path = "./image_s.xpm";
	char    *n_path = "./image_n.xpm";
	char	*w_path = "./image_w.xpm";
	char	*sprite_path = "./sprite.xpm";
	int fd;

	fd = open(argv[1], O_RDONLY);
	all.map = parcer(fd);
	all.win.mlx = mlx_init();
	all.win.win = mlx_new_window(all.win.mlx, width, height, "cub3d");
	all.win.img = mlx_new_image(all.win.mlx, width, height);
	all.win.addr = mlx_get_data_addr(all.win.img, &all.win.bpp, &all.win.line_len, &all.win.end);

	all.image_e.img = mlx_xpm_file_to_image(all.win.mlx, e_path, &all.image_e.img_width, &all.image_e.img_height);
	all.image_e.addr = mlx_get_data_addr(all.image_e.img, &all.image_e.bpp, &all.image_e.line_len, &all.image_e.end);

	all.image_s.img = mlx_xpm_file_to_image(all.win.mlx, s_path, &all.image_s.img_width, &all.image_s.img_height);
	all.image_s.addr = mlx_get_data_addr(all.image_s.img, &all.image_s.bpp, &all.image_s.line_len, &all.image_s.end);

	all.image_n.img = mlx_xpm_file_to_image(all.win.mlx, n_path, &all.image_n.img_width, &all.image_n.img_height);
	all.image_n.addr = mlx_get_data_addr(all.image_n.img, &all.image_n.bpp, &all.image_n.line_len, &all.image_n.end);

	all.image_w.img = mlx_xpm_file_to_image(all.win.mlx, w_path, &all.image_w.img_width, &all.image_w.img_height);
	all.image_w.addr = mlx_get_data_addr(all.image_w.img, &all.image_w.bpp, &all.image_w.line_len, &all.image_w.end);

	all.sprite.img = mlx_xpm_file_to_image(all.win.mlx, sprite_path, &all.sprite.img_width, &all.sprite.img_height);
	all.sprite.addr = mlx_get_data_addr(all.sprite.img, &all.sprite.bpp, &all.sprite.line_len, &all.sprite.end);

	fill_map_on_screen(&all);
	cast_ray(&all);
	mlx_put_image_to_window(all.win.mlx, all.win.win, all.win.img, 0, 0);

	if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 7) == 0)
			screenshot();
	mlx_hook(all.win.win, 17, 0L, close_win, &all);
	mlx_hook(all.win.win, 2, 1L<<0, key_hook, &all);
	mlx_loop(all.win.mlx);
}
