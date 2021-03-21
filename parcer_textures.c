/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:00:09 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/21 19:00:22 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char    *check_fill_no(int i, t_all *all)
{
    char    **strs;
    int        fd;

    strs = ft_split(all->map[i], ' ');
    if (strs_len(strs) != 2)
        return (NO);
    if ((ft_strrchr(strs[1], '.') == NULL)
            || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
        return (NO);
    all->image_n.path = ft_strdup(strs[1]);
    fd = open(all->image_n.path, O_RDONLY);
    if (fd == -1)
        return (PATH_NO);
    close(fd);
    if (all->image_n.path == NULL)
        return (NO);
    free_strs(strs);
    all->header.no++;
    return ("1");
}

char    *check_fill_so(int i, t_all *all)
{
    char    **strs;
    int        fd;

    strs = ft_split(all->map[i], ' ');
    if (strs_len(strs) != 2)
        return (SO);
    if ((ft_strrchr(strs[1], '.') == NULL)
            || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
        return (SO);
    all->image_s.path = ft_strdup(strs[1]);
    fd = open(all->image_s.path, O_RDONLY);
    if (fd == -1)
        return (PATH_SO);
    close(fd);
    if (all->image_s.path == NULL)
        return (SO);
    free_strs(strs);
    all->header.so++;
    return ("1");
}

char    *check_fill_we(int i, t_all *all)
{
    char    **strs;
    int        fd;

    strs = ft_split(all->map[i], ' ');
    if (strs_len(strs) != 2)
        return (WE);
    if ((ft_strrchr(strs[1], '.') == NULL)
            || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
        return (WE);
    all->image_w.path = ft_strdup(strs[1]);
    fd = open(all->image_w.path, O_RDONLY);
    if (fd == -1)
        return (PATH_WE);
    close(fd);
    if (all->image_w.path == NULL)
        return (WE);
    free_strs(strs);
    all->header.we++;
    return ("1");
}

char    *check_fill_ea(int i, t_all *all)
{
    char    **strs;
    int        fd;

    strs = ft_split(all->map[i], ' ');
    if (strs_len(strs) != 2)
        return (EA);
    if ((ft_strrchr(strs[1], '.') == NULL)
            || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
        return (EA);
    all->image_e.path = ft_strdup(strs[1]);
    fd = open(all->image_e.path, O_RDONLY);
    if (fd == -1)
        return (PATH_EA);
    close(fd);
    if (all->image_e.path == NULL)
        return (EA);
    free_strs(strs);
    all->header.ea++;
    return ("1");
}

char    *check_fill_s(int i, t_all *all)
{
    char    **strs;
    int        fd;

    strs = ft_split(all->map[i], ' ');
    if (strs_len(strs) != 2)
        return (S);
    if ((ft_strrchr(strs[1], '.') == NULL)
            || ft_strncmp(ft_strrchr(strs[1], '.'), ".xpm", 4) != 0)
        return (S);
    all->sprite.path = ft_strdup(strs[1]);
    fd = open(all->sprite.path, O_RDONLY);
    if (fd == -1)
        return (PATH_S);
    close(fd);
    if (all->sprite.path == NULL)
        return (S);
    free_strs(strs);
    all->header.s++;
    return ("1");
}
