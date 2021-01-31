#include "mlx.h"
#include "cub3d.h"
#include "libft.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
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

void	put_sqr(t_win *data, int x, int y, int color, int scl)
{
	int x_max;
	int y_max;
	int x_tmp;

	x_max = x + scl;
	y_max = y + scl;
	x_tmp = x;
	while (y <= y_max)
	{
		x = x_tmp;
		while (x <= x_max)
		{
			my_mlx_pixel_put(data, x, y, color);
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
			if (all->map[i][j] == 'N')
			{
				all->plr->x = x + SCALE / 2;
				all->plr->y = y + SCALE / 2;
				all->plr->dir = 0;
				all->map[i][j] = 1;
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
	int color = 0x0040FF;

	/* t_win	texture; */
	/* char    *relative_path = "./test.xpm"; */
	/* int     img_width; */
	/* int     img_height; */
	/* int		i; */
	/* int		j; */
	/* int		color; */
	/* float 	scl; */
	/* i = 0; */
	/* j = 0; */
	/* texture.img = mlx_xpm_file_to_image(all.win->mlx, relative_path, &img_width, &img_height); */
	/* texture.addr = mlx_get_data_addr(texture.img, &texture.bpp, &texture.line_len, &texture.end); */

	k = 0;
	distance = sqrt(x * x + y * y) * cos(all->plr->ray_dir - all->plr->dir);
	if (distance >= 20)
		line = 20 * 600 / distance;
	else
		line = 600;
	black = (600 - line) / 2;
	while (k < black)
	{
		my_mlx_pixel_put(all->win, i, k, 0x000000);
		k++;
	}
	while (k < line + black)
	{
		color =  0x0040FF - 20 * (int)(distance / 60);
		my_mlx_pixel_put(all->win, i, k, color);
		//	printf("%f\n", all->plr->y);
		if ((all->plr->x - (int)all->plr->x / SCALE * SCALE < 0.1) && all->plr->ray_dir > - M_PI_2 && all->plr->ray_dir < M_PI_2)
			my_mlx_pixel_put(all->win, i, k, 0xC800FF);
		else
		{
			color =  0x0040FF - 20 * (int)(distance / 60);
			my_mlx_pixel_put(all->win, i, k, color);
		}
		k++;
	}
	while (k < black * 2 + line)
	{
		my_mlx_pixel_put(all->win, i, k, 0x665E4F);
		k++;
	}
}

void	cast_ray(t_all *all)
{
	float dir_right;
	float x_tmp;
	float y_tmp;
	int i;

	i = 0;
	dir_right = all->plr->dir + M_PI / 6;
	all->plr->ray_dir = all->plr->dir - M_PI / 6;
	x_tmp = all->plr->x;
	y_tmp = all->plr->y;
	while (all->plr->ray_dir <= dir_right && i < 900)
	{
		while (all->map[(int)(all->plr->y / SCALE)][(int)(all->plr->x / SCALE)] != '1')
		{
			all->plr->x += 0.1 * cos(all->plr->ray_dir);
			all->plr->y += 0.1 * sin(all->plr->ray_dir);
			//		my_mlx_pixel_put(all->win, all->plr->x, all->ray_plr->y, 0x036BFC);
		}
		put_line(all, i, fabs(all->plr->x - x_tmp), fabs(all->plr->y - y_tmp));
		all->plr->x = x_tmp;
		all->plr->y = y_tmp;
		all->plr->ray_dir += M_PI / 3 / 900;
		i++;
	}
}

int	key_hook(int keycode, t_all *all)
{
	if (keycode == 119)
	{
		all->plr->x += cos(all->plr->dir) * 5;
		all->plr->y += sin(all->plr->dir) * 5;
	}
	if (keycode == 13)
	{
		all->plr->x += cos(all->plr->dir) * 5;
		all->plr->y += sin(all->plr->dir) * 5;
	}
	if (keycode == 1)
	{
		all->plr->x -= cos(all->plr->dir) * 5;
		all->plr->y -= sin(all->plr->dir) * 5;
	}
	if (keycode == 2)
		all->plr->dir += 0.15;
	if (keycode == 0)
		all->plr->dir -= 0.15;
//	printf("%f\n", all->plr->dir);
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
	t_all all;
	int fd;

	(void)argc;
	all.win = malloc(sizeof(t_win));
	all.plr = malloc(sizeof(t_plr));
	fd = open(argv[1], O_RDONLY);
	all.map = parcer(fd);
	all.win->mlx = mlx_init();
	all.win->win = mlx_new_window(all.win->mlx, 900, 600, "cub3d");
	all.win->img = mlx_new_image(all.win->mlx, 900, 600);
	all.win->addr = mlx_get_data_addr(all.win->img, &all.win->bpp, &all.win->line_len, &all.win->end);
	fill_map_on_screen(&all);
	cast_ray(&all);
	mlx_put_image_to_window(all.win->mlx, all.win->win, all.win->img, 0, 0);
	mlx_hook(all.win->win, 2, 1L<<0, key_hook, &all);
	mlx_loop(all.win->mlx);
}
