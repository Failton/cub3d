/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:03:31 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/22 13:47:33 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_argc(int argc, char **argv, int *fd)
{
	if (argc == 2 && (ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 5) != 0
	|| ft_strrchr(argv[1], '.') == 0))
	{
		printf("Error\nInvalid map format");
		return (0);
	}
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
	*fd = open(argv[1], O_RDONLY);
	if (*fd == -1)
	{
		printf("Error\n%s", strerror(errno));
		return (0);
	}
	return (1);
}

void	do_images(t_all *all)
{
	all->win.win = mlx_new_window(all->win.mlx, all->width,
			all->height, "cub3d");
	all->win.img = mlx_new_image(all->win.mlx, all->width, all->height);
	all->win.addr = mlx_get_data_addr(all->win.img, &all->win.bpp,
			&all->win.line_len, &all->win.end);
	all->image_e.img = mlx_xpm_file_to_image(all->win.mlx, all->image_e.path,
			&all->image_e.img_width, &all->image_e.img_height);
	all->image_e.addr = mlx_get_data_addr(all->image_e.img, &all->image_e.bpp,
			&all->image_e.line_len, &all->image_e.end);
	all->image_s.img = mlx_xpm_file_to_image(all->win.mlx, all->image_s.path,
			&all->image_s.img_width, &all->image_s.img_height);
	all->image_s.addr = mlx_get_data_addr(all->image_s.img, &all->image_s.bpp,
			&all->image_s.line_len, &all->image_s.end);
	all->image_n.img = mlx_xpm_file_to_image(all->win.mlx, all->image_n.path,
			&all->image_n.img_width, &all->image_n.img_height);
	all->image_n.addr = mlx_get_data_addr(all->image_n.img, &all->image_n.bpp,
			&all->image_n.line_len, &all->image_n.end);
	all->image_w.img = mlx_xpm_file_to_image(all->win.mlx, all->image_w.path,
			&all->image_w.img_width, &all->image_w.img_height);
	all->image_w.addr = mlx_get_data_addr(all->image_w.img, &all->image_w.bpp,
			&all->image_w.line_len, &all->image_w.end);
	all->sprite.img = mlx_xpm_file_to_image(all->win.mlx, all->sprite.path,
			&all->sprite.img_width, &all->sprite.img_height);
	all->sprite.addr = mlx_get_data_addr(all->sprite.img, &all->sprite.bpp,
			&all->sprite.line_len, &all->sprite.end);
}

int		main(int argc, char **argv)
{
	t_all	all;
	int		fd;

	if (check_argc(argc, argv, &fd) == 0)
		return (0);
	all.map = parcer(fd);
	all.win.mlx = mlx_init();
	fill_header(&all);
	if (check_cub(&all)[0] != '1')
	{
		close(fd);
		fill_header(&all);
		printf("Error\n%s", check_cub(&all));
		return (0);
	}
	do_images(&all);
	fill_map_on_screen(&all);
	cast_ray(&all);
	mlx_put_image_to_window(all.win.mlx, all.win.win, all.win.img, 0, 0);
	if (do_check_screenshot(argc, argv, &all, fd) == 0)
		return (0);
	mlx_hook(all.win.win, 17, 0L, close_win, &all);
	mlx_hook(all.win.win, 2, 1L << 0, key_hook, &all);
	mlx_loop(all.win.mlx);
	return (1);
}
