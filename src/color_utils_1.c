/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:03:00 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/22 11:03:01 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int				get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int				get_b(int trgb)
{
	return (trgb & 0xFF);
}

int				create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
