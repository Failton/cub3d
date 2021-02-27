#include "mlx.h"
#include "cub3d.h"
#include "libft.h"

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

unsigned int	my_mlx_get_color(t_win *data, int x, int y)
{
	char    *dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_win *all, int x, int y, int color)
{
	char    *dst;

	dst = all->addr + (y * all->line_len + x * (all->bpp / 8));
	*(unsigned int*)dst = color;
}

void	put_sqr_old(t_win *data, int x, int y, char smbl)
{
	int x_max;
	int y_max;
	int x_tmp;

	x_max = x + SCALE;
	y_max = y + SCALE;
	x_tmp = x;
	while (y < y_max)
	{
		x = x_tmp;
		while (x < x_max)
		{
			if (smbl == '1')
				my_mlx_pixel_put(data, x, y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
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
		//	put_sqr(all->win, x, y, all->map[i][j]);
			if (all->map[i][j] == 'N')
			{
				all->plr->x = x + SCALE / 2;
				all->plr->y = y + SCALE / 2;
				all->plr->dir = M_PI;
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

void	put_line(t_all *all, int i, float x, float y)
{
	float distance;
	float line;
	float black;
	int k;
	int color = 0x000040FF;

	k = 0;
	distance = sqrt(x * x + y * y) * fabs(cos(all->plr->ray_start - all->plr->dir));
	if (distance >= SCALE)
		line = SCALE * 600 / distance;
	else
		line = 600;
	black = (600 - line) / 2;
	while (k < black)
	{
		my_mlx_pixel_put(all->win, i, k, 0x00000000);
		k++;
	}
	while (k < line + black)
	{
		color =  0x000040FF - SCALE * (int)(distance / SCALE);
		my_mlx_pixel_put(all->win, i, k, color);
		k++;
	}
	while (k < black * 2 + line)
	{
		my_mlx_pixel_put(all->win, i, k, 0x00665E4F);
		k++;
	}
}

void	horizont_point(t_all *all, t_point *point)	
{
	float temp_x;
	float temp_y;

	temp_x = point->x;
	temp_y = point->y;
	if ((all->plr->ray_start >= - M_PI && all->plr->ray_start <= 0) || (all->plr->ray_start >= M_PI && all->plr->ray_start <= 3 * M_PI_2))
		point->y = (int)(temp_y / SCALE) * SCALE - 0.00009;
	else
		point->y = (int)(temp_y / SCALE) * SCALE + SCALE;
	point->x = temp_x - (temp_y - point->y) / tan(all->plr->ray_start);
	point->len =  sqrt(pow((all->plr->x - point->x), 2) + pow((all->plr->y - point->y), 2));
}

void	vertical_point(t_all *all, t_point *point)	
{
	float temp_x;
	float temp_y;

	temp_x = point->x;
	temp_y = point->y;
	if ((all->plr->ray_start >= - M_PI_2 && all->plr->ray_start <= M_PI_2) || (all->plr->ray_start <= - 3 * M_PI_2 && all->plr->ray_start >= - 2 * M_PI))
		point->x = (int)(temp_x / SCALE) * SCALE + SCALE;
	else
		point->x = (int)(temp_x / SCALE) * SCALE - 0.00009;
	point->y = temp_y - (temp_x - point->x) * tan(all->plr->ray_start);
	point->len =  sqrt(pow((all->plr->x - point->x), 2) + pow((all->plr->y - point->y), 2));
}

void	put_image_e(t_all *all, int i, float x, float y)
{
	int		k;
	unsigned int		color;
	float 	scl;

	float line;
	float black;

	k = 0;
	line = SCALE * 600 / (sqrt(pow(all->plr->x - x, 2) + pow(all->plr->y - y, 2)) * fabs(cos(all->plr->ray_start - all->plr->dir)));
	if (line >= 600)
		line = 0;
	color = 0;
	scl = line / all->image_e->img_height;
	black = (600 - line) / 2;
	while (k < black)
	{
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00000000);
		k++;
	}
	while (k < line + black)
	{
		color = my_mlx_get_color(all->image_e, (int)((y - (int)(y / SCALE) * SCALE) / SCALE * all->image_e->img_width), (k - black) / scl);
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, color);
		k++;
	}
	while (k < black * 2 + line)
	{
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00665E4F);
		k++;
	}
}

void	put_image_w(t_all *all, int i, float x, float y)
{
	int		k;
	int		color;
	float 	scl;

	float line;
	float black;

	k = 0;
	line = SCALE * 600 / (sqrt(pow(all->plr->x - x, 2) + pow(all->plr->y - y, 2)) * fabs(cos(all->plr->ray_start - all->plr->dir)));
	if (line >= 600)
		line = 0;
	color = 0;
	scl = line / all->image_w->img_height;
	black = (600 - line) / 2;
	while (k < black)
	{
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00000000);
		k++;
	}
	while (k < line + black)
	{
		color = my_mlx_get_color(all->image_w, (int)(all->image_w->img_width - (y - (int)(y / SCALE) * SCALE) / SCALE * all->image_w->img_width), (k - black) / scl);
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, color);
		k++;
	}
	while (k < black * 2 + line)
	{
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00665E4F);
		k++;
	}
}

void	put_image_n(t_all *all, int i, float x, float y)
{
	int		k;
	int		color;
	float 	scl;

	float line;
	float black;

	k = 0;
	line = SCALE * 600 / (sqrt(pow(all->plr->x - x, 2) + pow(all->plr->y - y, 2)) * fabs(cos(all->plr->ray_start - all->plr->dir)));
	if (line >= 600)
		line = 0;
	color = 0;
	scl = line / all->image_n->img_height;
	black = (600 - line) / 2;
	while (k < black)
	{
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00000000);
		k++;
	}
	while (k < line + black)
	{
		color = my_mlx_get_color(all->image_n, (int)((x - (int)(x / SCALE) * SCALE) / SCALE * all->image_n->img_width), (k - black) / scl);
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, color);
		k++;
	}
	while (k < black * 2 + line)
	{
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00665E4F);
		k++;
	}
}

void	put_image_s(t_all *all, int i, float x, float y)
{
	int		k;
	int		color;
	float 	scl;

	float line;
	float black;

	k = 0;
	line = SCALE * 600 / (sqrt(pow(all->plr->x - x, 2) + pow(all->plr->y - y, 2)) * fabs(cos(all->plr->ray_start - all->plr->dir)));
	if (line >= 600)
		line = 0;
	color = 0;
	scl = line / all->image_s->img_height;
	black = (600 - line) / 2;
	while (k < black)
	{
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00000000);
		k++;
	}
	while (k < line + black)
	{
		color = my_mlx_get_color(all->image_s, (int)(all->image_s->img_width - (x - (int)(x / SCALE) * SCALE) / SCALE * all->image_s->img_width), (k - black) / scl);
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, color);
		k++;
	}
	while (k < black * 2 + line)
	{
		if (my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, 0x00665E4F);
		k++;
	}
}

void		find_line(t_all *all, float *x1, float *y1)
{
	float x2;
	float y2;
	float a1;
	float b1;
	float c1;

	float x3;
	float y3;
	float a2;
	float b2;
	float c2;

	if ((all->plr->dir >= 0 && all->plr->dir <= M_PI_2) || (all->plr->dir >= - M_PI && all->plr->dir <= - M_PI_2))
		x2 = *x1 - tan(all->plr->dir) * SCALE;
	else
		x2 = *x1 + tan(all->plr->dir) * SCALE;
	if (all->plr->dir == 0 || all->plr->dir == - M_PI || all->plr->dir == M_PI)
		y2 = *y1 + SCALE;
	else
		y2 = *y1 + 1 / tan(all->plr->dir) * SCALE;
	a1 = *y1 - y2;
	b1 = x2 - *x1;
	c1 = *x1 * y2 - x2 * *y1;
	
	x3 = all->plr->x + cos(all->plr->ray_start) * SCALE;
	y3 = all->plr->y + sin(all->plr->ray_start) * SCALE;
	a2 = all->plr->y - y3;
	b2 = x3 - all->plr->x;
	c2 = all->plr->x * y3 - x3 * all->plr->y;

	if ((int)(((a1 * c2 - a2 * c1) / (a2 * b1 - a1 * b2)) / SCALE) == (int)(*y1 / SCALE))
		*y1 = (a1 * c2 - a2 * c1) / (a2 * b1 - a1 * b2);
	else
		*y1 = -1;
	if ((int)((- (b2 / a2) * *y1 - (c2 / a2)) / SCALE) == (int)(*x1 / SCALE))
		*x1 = - (b2 / a2) * *y1 - (c2 / a2);
	else
		*x1 = -1;
}

void	put_sprite(t_all *all, int i, float x, float y)
{
	int		k;
	unsigned int	color;
	float 	scl;
	float	tmp_x;
	float	tmp_y;

	float line;
	float black;

	k = 0;
	tmp_x = (int)(x / SCALE) * SCALE + SCALE / 2;
	tmp_y = (int)(y / SCALE) * SCALE + SCALE / 2;
	line = SCALE * 600 / (sqrt(pow(all->plr->x - tmp_x, 2) + pow(all->plr->y - tmp_y, 2)));
	find_line(all, &tmp_x, &tmp_y);
	if (line >= 600)
		line = 0;
	color = 0;
	scl = line / all->sprite->img_height;
	black = (600 - line) / 2;
	while (k < black)
		k++;
	while (k < line + black)
	{
		if (tmp_y != -1 && tmp_x != -1 && all->plr->dir >= - M_PI / 4 && all->plr->dir <= M_PI / 4)
			color = my_mlx_get_color(all->sprite, (int)((tmp_y - (int)(tmp_y / SCALE) * SCALE) / SCALE * all->sprite->img_width), (k - black) / scl);
		else if (tmp_y != -1 && tmp_x != -1 && ((all->plr->dir <= - 3 * M_PI_4 && all->plr->dir >= - 5 * M_PI_4) || (all->plr->dir <= M_PI && all->plr->dir >= 3 * M_PI_4)))
			color = my_mlx_get_color(all->sprite, (int)(all->sprite->img_width - (tmp_y - (int)(tmp_y / SCALE) * SCALE) / SCALE * all->sprite->img_width), (k - black) / scl);
		else if (tmp_y != -1 && tmp_x != -1 && all->plr->dir >= - 3 * M_PI_4 && all->plr->dir <= - M_PI_4)
			color = my_mlx_get_color(all->sprite, (int)((tmp_x - (int)(tmp_x / SCALE) * SCALE) / SCALE * all->sprite->img_width), (k - black) / scl);
		else if (tmp_y != -1 && tmp_x != -1)
			color = my_mlx_get_color(all->sprite, (int)(all->sprite->img_width - (tmp_x - (int)(tmp_x / SCALE) * SCALE) / SCALE * all->sprite->img_width), (k - black) / scl);
		if (color != 4278190080 && tmp_y != -1 && tmp_y != -1 && my_mlx_get_color(all->win, i, k) == 0)
			my_mlx_pixel_put(all->win, i, k, color);
		k++;
	}
	while (k < black * 2 + line)
		k++;
}

void	cast_ray(t_all *all)
{
	t_point point_hor;
	t_point point_vert;
	float x;
	float y;
	int i;

	i = 0;
	point_hor.x = all->plr->x;
	point_hor.y = all->plr->y;
	point_vert.x = all->plr->x;
	point_vert.y = all->plr->y;
	all->plr->ray_end = all->plr->dir + M_PI / 6;
	all->plr->ray_start = all->plr->dir - M_PI / 6;
	x = all->plr->x;
	y = all->plr->y;
	while (all->plr->ray_start <= all->plr->ray_end && i < 900)
	{
		horizont_point(all, &point_hor);
		vertical_point(all, &point_vert);
		point_hor.flag = 0;
		point_vert.flag = 0;
		while (all->map[(int)(y / SCALE)][(int)(x / SCALE)] != '1')
		{
			//	my_mlx_pixel_put(all->win, x, y, 0x00182ded);
			if (all->map[(int)(y / SCALE)][(int)(x / SCALE)] == '2')
			{
				put_sprite(all, i, x, y);
				/* printf("===============================\n"); */
			}
			if (point_hor.len < point_vert.len)
			{
				x = point_hor.x;
				y = point_hor.y;
				point_hor.flag = 1;
				point_vert.flag = 0;
				horizont_point(all, &point_hor);
			}
			else
			{
				x = point_vert.x;
				y = point_vert.y;
				point_hor.flag = 0;
				point_vert.flag = 1;
				vertical_point(all, &point_vert);
			}
		}
		if (point_vert.flag == 1 && ((all->plr->ray_start >= - M_PI_2 && all->plr->ray_start <= M_PI_2) || (all->plr->ray_start <= - 3 * M_PI_2 && all->plr->ray_start >= - 2 * M_PI)))
			put_image_e(all, i, x, y);
		else if (point_vert.flag == 1)
			put_image_w(all, i, x, y);
		else if (point_hor.flag == 1 && ((all->plr->ray_start >= - M_PI && all->plr->ray_start <= 0) || (all->plr->ray_start >= M_PI && all->plr->ray_start <= 3 * M_PI_2)))
			put_image_n(all, i, x, y);
		else
			put_image_s(all, i, x, y);
		i++;
		all->plr->ray_start = - atan((450 - i) / (sqrt(3) * 450)) + all->plr->dir;

		//	my_mlx_pixel_put(all->win, x, y, 0x00FF0000);
		x = all->plr->x;
		y = all->plr->y;
		point_hor.x = all->plr->x;
		point_hor.y = all->plr->y;
		point_vert.x = all->plr->x;
		point_vert.y = all->plr->y;
	}
}

int	key_hook(int keycode, t_all *all)
{
	/* printf("%d\n", keycode); */
	if (keycode == 13 || keycode == 119)
	{
		all->plr->x += cos(all->plr->dir) * 0.4 * SCALE;
		all->plr->y += sin(all->plr->dir) * 0.4 * SCALE;
	}
	if (keycode == 1 || keycode == 115)
	{
		all->plr->x -= cos(all->plr->dir) * 0.4 * SCALE;
		all->plr->y -= sin(all->plr->dir) * 0.4 * SCALE;
	}
	if (keycode == 123 || keycode == 65361)
	{
		all->plr->x += sin(all->plr->dir) * 0.4 * SCALE;
		all->plr->y -= cos(all->plr->dir) * 0.4 * SCALE;
	}
	if (keycode == 124 || keycode == 65363)
	{
		all->plr->x -= sin(all->plr->dir) * 0.4 * SCALE;
		all->plr->y += cos(all->plr->dir) * 0.4 * SCALE;
	}
	if (keycode == 2 || keycode == 100)
		all->plr->dir += 0.15;
	if (keycode == 0 || keycode == 97)
		all->plr->dir -= 0.15;
	if (all->plr->dir <= - 3 * M_PI_2)
		all->plr->dir += 2 * M_PI;
	if (all->plr->dir >= M_PI)
		all->plr->dir -= 2 * M_PI;
	mlx_destroy_image(all->win->mlx, all->win->img);
	all->win->img = mlx_new_image(all->win->mlx, 900, 600);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bpp, &all->win->line_len, &all->win->end);
//	fill_map_on_screen(all);
	cast_ray(all);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
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

int main(int argc, char **argv)
{
	char    *e_path = "./image_e.xpm";
	/* char    *e_path = "./light.xpm"; */
	char	*s_path = "./image_s.xpm";
	char    *n_path = "./image_n.xpm";
	char	*w_path = "./image_w.xpm";
	char	*sprite_path = "./sprite.xpm";
	t_all all;
	int fd;

	(void)argc;
	all.win = malloc(sizeof(t_win));
	all.plr = malloc(sizeof(t_plr));
	all.image_e = malloc(sizeof(t_win));
	all.image_s = malloc(sizeof(t_win));
	all.image_n = malloc(sizeof(t_win));
	all.image_w = malloc(sizeof(t_win));
	all.sprite = malloc(sizeof(t_win));


	fd = open(argv[1], O_RDONLY);
	all.map = parcer(fd);
	all.win->mlx = mlx_init();
	all.win->win = mlx_new_window(all.win->mlx, 900, 600, "cub3d");
	all.win->img = mlx_new_image(all.win->mlx, 900, 600);
	all.win->addr = mlx_get_data_addr(all.win->img, &all.win->bpp, &all.win->line_len, &all.win->end);

	/* printf("%u\n", my_mlx_get_color(all.win, 10, 10)); */
	all.image_e->img = mlx_xpm_file_to_image(all.win->mlx, e_path, &all.image_e->img_width, &all.image_e->img_height);
	all.image_e->addr = mlx_get_data_addr(all.image_e->img, &all.image_e->bpp, &all.image_e->line_len, &all.image_e->end);

	all.image_s->img = mlx_xpm_file_to_image(all.win->mlx, s_path, &all.image_s->img_width, &all.image_s->img_height);
	all.image_s->addr = mlx_get_data_addr(all.image_s->img, &all.image_s->bpp, &all.image_s->line_len, &all.image_s->end);

	all.image_n->img = mlx_xpm_file_to_image(all.win->mlx, n_path, &all.image_n->img_width, &all.image_n->img_height);
	all.image_n->addr = mlx_get_data_addr(all.image_n->img, &all.image_n->bpp, &all.image_n->line_len, &all.image_n->end);

	all.image_w->img = mlx_xpm_file_to_image(all.win->mlx, w_path, &all.image_w->img_width, &all.image_w->img_height);
	all.image_w->addr = mlx_get_data_addr(all.image_w->img, &all.image_w->bpp, &all.image_w->line_len, &all.image_w->end);

	all.sprite->img = mlx_xpm_file_to_image(all.win->mlx, sprite_path, &all.sprite->img_width, &all.sprite->img_height);
	all.sprite->addr = mlx_get_data_addr(all.sprite->img, &all.sprite->bpp, &all.sprite->line_len, &all.sprite->end);

	fill_map_on_screen(&all);
	cast_ray(&all);
	mlx_put_image_to_window(all.win->mlx, all.win->win, all.win->img, 0, 0);
	mlx_hook(all.win->win, 2, 1L<<0, key_hook, &all);
	mlx_loop(all.win->mlx);
}
