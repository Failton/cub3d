/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_circuit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:05:53 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/22 11:05:54 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*check_circuit_start(t_all all, int i, int j, int start)
{
	if ((i == start) || (j == 0) || (j > (int)ft_strlen(all.map
					[i - 1])) || all.map[i - 1][j - 1] == ' ')
		return (BAD_CIRCUIT);
	if ((i == start) || (j > (int)ft_strlen(all.map[i - 1]) - 1)
			|| all.map[i - 1][j] == ' ')
		return (BAD_CIRCUIT);
	if ((i == start) || (j > (int)ft_strlen(all.map[i - 1]) - 2)
			|| all.map[i - 1][j + 1] == ' ')
		return (BAD_CIRCUIT);
	if ((j > (int)ft_strlen(all.map[i]) - 2) || all.map[i][j + 1]
			== ' ')
		return (BAD_CIRCUIT);
	return ("1");
}

char	*check_circuit_end(t_all all, int i, int j, int end)
{
	if ((i == end) || (j > (int)ft_strlen(all.map[i + 1]) - 2)
			|| all.map[i + 1][j + 1] == ' ')
		return (BAD_CIRCUIT);
	if ((i == end) || (j > (int)ft_strlen(all.map[i + 1]) - 1)
			|| all.map[i + 1][j] == ' ')
		return (BAD_CIRCUIT);
	if ((i == end) || (j == 0) || (j > (int)ft_strlen(all.map
					[i + 1])) || all.map[i + 1][j - 1] == ' ')
		return (BAD_CIRCUIT);
	if ((j == 0) || (j > (int)ft_strlen(all.map[i]))
			|| all.map[i][j - 1] == ' ')
		return (BAD_CIRCUIT);
	return ("1");
}

char	*check_circuit(int i, int end, t_all all)
{
	int j;
	int start;

	j = 0;
	start = i;
	while (all.map[i] != 0)
	{
		j = 0;
		while (all.map[i][j] != 0)
		{
			if (all.map[i][j] == '0' || all.map[i][j] == '2'
					|| all.map[i][j] == 'N' || all.map[i][j] == 'W'
					|| all.map[i][j] == 'S' || all.map[i][j] == 'E')
			{
				if (check_circuit_start(all, i, j, start)[0] != '1' ||
						check_circuit_end(all, i, j, end)[0] != '1')
					return (BAD_CIRCUIT);
			}
			j++;
		}
		i++;
	}
	return ("1");
}
