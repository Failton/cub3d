#include "mlx.h"
#include "cub3d.h"
#include "libft.h"

void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	ft_cast_ray(char **map, t_plr ray, t_win *data)
{
	while (map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
	{
		ray.x += cos(ray.dir);
		ray.y += sin(ray.dir);
		my_mlx_pixel_put(data, ray.x, ray.y, 0x990099);
	}
}

void	put_sqr(t_win *data, int x, int y, char smbl)
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
				my_mlx_pixel_put(data, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
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
	t_win img;
	t_plr ray;
	int i;
	int j;
	char **map;
	int fd;
	int x;
	int y;

	(void)argc;
	i = 0;
	j = 0;
	x = 0;
	y = 0;
	fd = open(argv[1], O_RDONLY);
	map = parcer(fd);
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 900, 600, "cub3d");
	img.img = mlx_new_image(img.mlx, 900, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.end);
	while (map[i])
	{
		x = 0;
		j = 0;
		while (map[i][j])
		{
			put_sqr(&img, x, y, map[i][j]);
			if (map[i][j] == 'N')
			{
				ray.x = x + SCALE / 2;
				ray.y = y + SCALE / 2;
				ray.dir = -1.5;
			}
			x += SCALE;
			j++;
		}
		y += SCALE;
		i++;
	}
	ft_cast_ray(map, ray, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_loop(img.mlx);
}
