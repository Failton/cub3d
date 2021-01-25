#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include "cub3d.h"

void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
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
//	t_win img;
	int i;
	int j;
	char **map;
	int fd;
	int k;

	(void)argc;
	i = 50;
	j = 50;
	k = 0;
	fd = open(argv[1], O_RDONLY);
	map = parcer(fd);
	while (map[k])
	{
		ft_putendl_fd(map[k], 1);
		k++;
	}
	/* img.mlx = mlx_init(); */
	/* img.win = mlx_new_window(img.mlx, 640, 480, "cub3d"); */
	/* img.img = mlx_new_image(img.mlx, 640, 480); */
	/* img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.end); */
	/*  */
	/* mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0); */
	/* mlx_loop(img.mlx); */
}
