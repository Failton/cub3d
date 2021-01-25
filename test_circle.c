#include "mlx.h"
#include "cub3d.h"

void            my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int main()
{
	t_win img;
	int a;
	int b;
	int r;
	int g;

	a = 100;
	b = 100;
	r = 50;
	g = 0;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 640, 480, "cub3d");
	img.img = mlx_new_image(img.mlx, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.end);
	while (g < 360)
	{
		my_mlx_pixel_put(&img, (a + r * cos(g * M_PI / 180)), (a + r * sin(g * M_PI / 180)), 0xFFFFFF);
		g++;
	}
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_loop(img.mlx);
}
