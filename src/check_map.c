/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:02:46 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/22 13:19:30 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*check_player(int i, t_all all)
{
	int j;
	int count;

	count = 0;
	j = 0;
	while (all.map[i] != 0)
	{
		j = 0;
		while (all.map[i][j] != 0)
		{
			if (all.map[i][j] == 'N' || all.map[i][j] == 'W'
					|| all.map[i][j] == 'S' || all.map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (PLAYER);
	return ("1");
}

char	*check_symbols(int i, t_all all)
{
	int j;
	int temp_i;

	temp_i = i;
	j = 0;
	while (all.map[i] != 0)
	{
		j = 0;
		if (ft_strlen(all.map[i]) == 0)
			return (MAP_EMPTY_LINE);
		while (all.map[i][j])
		{
			if (all.map[i][j] != ' ' && all.map[i][j] != '1'
					&& all.map[i][j] != '0' && all.map[i][j] != 'N'
					&& all.map[i][j] != 'W' && all.map[i][j] != 'S'
					&& all.map[i][j] != 'E' && all.map[i][j] != '2')
				return (MAP_WRONG_SYMBOLS);
			j++;
		}
		i++;
	}
	if (check_circuit(temp_i, i - 1, all)[0] != '1')
		return (BAD_CIRCUIT);
	return ("1");
}

char	*check_map(int i, t_all all)
{
	if (check_symbols(i, all)[0] != '1')
		return (check_symbols(i, all));
	if (check_player(i, all)[0] != '1')
		return (check_player(i, all));
	return ("1");
}
