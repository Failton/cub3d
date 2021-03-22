/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:06:17 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/22 11:06:19 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	screenshot_filler(t_shot *shot, t_all all)
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

void	screenshot_header(int fd, t_all all)
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

void	screenshot_trgb(int fd, int color)
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

int		screenshot(t_all all)
{
	int fd;
	int x;
	int y;
	int color;

	x = 0;
	y = all.height;
	fd = open("img.bmp", O_CREAT | O_RDWR | O_TRUNC);
	screenshot_header(fd, all);
	if (fd == -1)
		return (0);
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
	return (1);
}

int		do_check_screenshot(int argc, char **argv, t_all *all, int fd)
{
	if ((argc == 3) && ft_strncmp(argv[2], "--save", 7) == 0)
	{
		close(fd);
		if (screenshot(*all) == 0)
		{
			perror("Error");
			close_win(all);
			return (0);
		}
		close_win(all);
	}
	else if ((argc == 3) && ft_strncmp(argv[2], "--save", 7) != 0)
	{
		printf("Error\nInvalid arguments");
		close_win(all);
	}
	return (1);
}
