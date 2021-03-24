/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruthann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:02:28 by pruthann          #+#    #+#             */
/*   Updated: 2021/03/24 18:34:47 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*check_ident(int *i, t_all *all, int argc)
{
	char *answer;

	if (ft_strlen(all->map[*i]) == 0)
		return ("1");
	else if (ft_strncmp(all->map[*i], "R ", 2) == 0)
		answer = check_fill_res(*i, all, argc);
	else if (ft_strncmp(all->map[*i], "NO ", 3) == 0)
		answer = check_fill_no(*i, all);
	else if (ft_strncmp(all->map[*i], "SO ", 3) == 0)
		answer = check_fill_so(*i, all);
	else if (ft_strncmp(all->map[*i], "WE ", 3) == 0)
		answer = check_fill_we(*i, all);
	else if (ft_strncmp(all->map[*i], "EA ", 3) == 0)
		answer = check_fill_ea(*i, all);
	else if (ft_strncmp(all->map[*i], "S ", 2) == 0)
		answer = check_fill_s(*i, all);
	else if (ft_strncmp(all->map[*i], "F ", 2) == 0)
		answer = check_fill_f(*i, all);
	else if (ft_strncmp(all->map[*i], "C ", 2) == 0)
		answer = check_fill_c(*i, all);
	else
		return ("0");
	if (answer[0] != '1')
		return (answer);
	return ("1");
}

int		check_empty_line(int i, t_all all)
{
	int j;

	j = 0;
	while (all.map[i][j])
	{
		if (all.map[i][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int		check_line(int i, t_all all)
{
	int j;

	j = 0;
	while (all.map[i][j] != 0)
	{
		if (all.map[i][j] != ' ' && all.map[i][j] != '1'
				&& all.map[i][j] != '0' && all.map[i][j] != 'N'
				&& all.map[i][j] != 'W' && all.map[i][j] != 'S'
				&& all.map[i][j] != 'E' && all.map[i][j] != '2')
			return (0);
		j++;
	}
	return (1);
}

char	*check_cub(t_all *all, int a)
{
	int i;

	i = 0;
	if (all->map[i] == 0)
		return (EMPTY_FILE);
	while (check_ident(&i, all, a)[0] == '1')
		if (all->map[++i - 1] == 0)
			break ;
	if (all->map[i] == 0 && check_header(*all)[0] != '1')
		return (check_header(*all));
	if (check_ident(&i, all, a)[0] == '1')
		return (NO_MAP);
	if (check_empty_line(i, *all) == 0)
		return (WRONG_LINE);
	if (check_ident(&i, all, a)[0] != '0' && check_ident(&i, all, a)[0] != '1')
		return (check_ident(&i, all, a));
	if (check_ident(&i, all, a)[0] == '0' && check_header_dublicates(*all) == 1
	&& check_header(*all)[0] != '1' && check_line(i, *all) == 0)
		return (WRONG_LINE);
	if (check_header(*all)[0] != '1')
		return (check_header(*all));
	if (check_map(i, *all)[0] != '1')
		return (check_map(i, *all));
	return ("1");
}
