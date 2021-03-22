/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:03:15 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/22 11:03:16 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	my_mlx_get_color(t_win data, int x, int y)
{
	char	*dst;

	dst = data.addr + (y * data.line_len + x * (data.bpp / 8));
	return (*(unsigned int *)dst);
}

void			my_mlx_pixel_put(t_win all, int x, int y, int color)
{
	char	*dst;

	dst = all.addr + (y * all.line_len + x * (all.bpp / 8));
	*(unsigned int*)dst = color;
}
