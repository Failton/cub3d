#include "mlx.h"
#include "cub3d.h"

t_all all;
int width = 64;
int height = 64;

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

int    my_mlx_get_color(t_win data, int x, int y)
{
        char *dst;

        dst = data.addr + (y * data.line_len + x * (data.bpp / 8));
        return (*(int *)dst);
}

void screenshot(int fd)
{
	unsigned char signature[2] = "BM";
	unsigned int filesize = 14 + 40 + width*height*4;
	unsigned int reserved = 0;
	unsigned int offset = 14 + 40;

	unsigned int headersize = 40;
	unsigned int dimensions[2] = { width, height };
	unsigned short colorplanes = 1;
	unsigned short bpp = 32;
	unsigned int compression = 0;
	unsigned int imgsize = 64*64*4;
	unsigned int resolution[2] = { 2795, 2795 };
	unsigned int pltcolors = 0;
	unsigned int impcolors = 0;

	unsigned char r, g, b, t;
	int x, y, color;

	x = 0;
	y = height;
	t = 0;

	write(fd, (char *)(signature), sizeof(signature));
	write(fd, (char *)(&filesize), sizeof(filesize));
	write(fd, (char *)(&reserved), sizeof(reserved));
	write(fd, (char *)(&offset), sizeof(offset));

	write(fd, (char *)(&headersize), sizeof(headersize));
	write(fd, (char *)(dimensions), sizeof(dimensions));
	write(fd, (char *)(&colorplanes), sizeof(colorplanes));
	write(fd, (char *)(&bpp), sizeof(bpp));
	write(fd, (char *)(&compression), sizeof(compression));
	write(fd, (char *)(&imgsize), sizeof(imgsize));
	write(fd, (char *)(resolution), sizeof(resolution));
	write(fd, (char *)(&pltcolors), sizeof(pltcolors));
	write(fd, (char *)(&impcolors), sizeof(impcolors));

	while (y - 1 >= 0)
	{
		x = 0;
		while (x < width)
		{
			color = my_mlx_get_color(all.image_n, x, y - 1);
			printf("%d %c\n", color, get_r(color) / 65536);
			r = get_r(color) / 65536;
			g = get_g(color) / 256;
			b = get_b(color);
			/* r = (unsigned char)(get_r(my_mlx_get_color(all.image_n, x, y))); */
			/* g = (unsigned char)(get_g(my_mlx_get_color(all.image_n, x, y))); */
			/* b = (unsigned char)(get_b(my_mlx_get_color(all.image_n, x, y))); */

			printf("|%d| |%d| |%d|\n", r, g, b);
			write(fd, (char *)(&b), sizeof(b));
			write(fd, (char *)(&g), sizeof(g));
			write(fd, (char *)(&r), sizeof(r));
			write(fd, (char *)(&t), sizeof(t));
			x++;
		}
		y--;
	}
}
int main(int argc, char **argv)
{
	char    *w_path = "./image_n.xpm";
	(void)argc;
	(void)argv;
	int fd;
	all.win.mlx = mlx_init();
	all.win.win = mlx_new_window(all.win.mlx, width, height, "cub3d");

	all.image_n.img = mlx_xpm_file_to_image(all.win.mlx, w_path, &all.image_n.img_width, &all.image_n.img_height);
	all.image_n.addr = mlx_get_data_addr(all.image_n.img, &all.image_n.bpp, &all.image_n.line_len, &all.image_n.end);

	mlx_put_image_to_window(all.win.mlx, all.win.win, all.image_n.img, 0, 0);

	fd = open("img.bmp", O_CREAT | O_RDWR | O_TRUNC);
	screenshot(fd);
	close(fd);
	mlx_loop(all.win.mlx);
}
