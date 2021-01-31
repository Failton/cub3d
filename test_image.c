#include "cub3d.h"
#include "mlx.h"

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

void	my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char    *dst;

	dst = win->addr + (y * win->line_len + x * (win->bpp / 8));
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

int     main(void)
{
	t_all all;
	t_win	texture;
	char    *relative_path = "./test.xpm";
	int     img_width;
	int     img_height;
	int		i;
	int		j;
	float 	line;
	int		color;
	float 	scl;

	i = 0;
	j = 0;
	line = 400;
	color = 0;
	all.win = malloc(sizeof(t_win));
	all.plr = malloc(sizeof(t_plr));
	all.win->mlx = mlx_init();
	all.win->img = mlx_new_image(all.win->mlx, 900, 600);
	all.win->win = mlx_new_window(all.win->mlx, 900, 600, "cub3d");
	texture.img = mlx_xpm_file_to_image(all.win->mlx, relative_path, &img_width, &img_height);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bpp, &texture.line_len, &texture.end);



	all.win->addr = mlx_get_data_addr(all.win->img, &all.win->bpp, &all.win->line_len, &all.win->end);
	all.plr->x = 0;
	all.plr->y = 0;
	scl = line / img_height;
	while (j < img_width)
	{
		all.plr->y = 0;
		i = 0;
		while (i < img_height)
		{
			color = my_mlx_get_color(&texture, (int)(j), (int)i);
			put_sqr(all.win, all.plr->x, all.plr->y, color, scl);
			printf("%d\n", color);
		//	my_mlx_pixel_put(all.win, (int)j, (int)i, color);
			i++;
			all.plr->y += scl;
			printf("%d\n", i);
		}
		all.plr->x += scl;
		j++;
	}


	mlx_put_image_to_window(all.win->mlx, all.win->win, all.win->img, 0, 0);
	printf("%d  %d\n", img_width, img_height);
	mlx_loop(all.win->mlx);
}
