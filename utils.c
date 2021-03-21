/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:12:10 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/21 19:12:11 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int                close_win(t_all *all)
{
    free(all->image_n.path);
    free(all->image_e.path);
    free(all->image_w.path);
    free(all->image_s.path);
    free(all->sprite.path);
    mlx_destroy_image(all->win.mlx, all->image_n.img);
    mlx_destroy_image(all->win.mlx, all->image_e.img);
    mlx_destroy_image(all->win.mlx, all->image_w.img);
    mlx_destroy_image(all->win.mlx, all->image_s.img);
    mlx_destroy_image(all->win.mlx, all->sprite.img);
    mlx_clear_window(all->win.mlx, all->win.win);
    mlx_destroy_window(all->win.mlx, all->win.win);
    exit(1);
    return (1);
}

int                fill_map_on_screen(t_all *all)
{
    int    i;
    int    j;

    i = 0;
    j = 0;
    while (all->map[i])
    {
        j = 0;
        while (all->map[i][j])
        {
            if (all->map[i][j] == 'N' || all->map[i][j] == 'W' ||
                    all->map[i][j] == 'S' || all->map[i][j] == 'E')
            {
                all->plr.x = j * SCALE + SCALE / 2;
                all->plr.y = i * SCALE + SCALE / 2;
                choose_dir(all, i, j);
                all->map[i][j] = '0';
            }
            j++;
        }
        i++;
    }
    return (1);
}

char            **parcer(int fd)
{
    char    **map;
    char    *line;
    int        i;
    t_list    *map_list;
    t_list    *temp;

    map_list = NULL;
    while (get_next_line(fd, &line))
        ft_lstadd_back(&map_list, ft_lstnew(line));
    ft_lstadd_back(&map_list, ft_lstnew(line));
    map = ft_calloc(ft_lstsize(map_list) + 1, sizeof(char *));
    i = 0;
    while (map_list)
    {
        map[i] = map_list->content;
        temp = map_list;
        map_list = map_list->next;
        free(temp);
        i++;
    }
    free(map[i - 1]);
    map[i - 1] = NULL;
    return (map);
}
