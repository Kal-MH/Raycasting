/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:41:51 by mkal              #+#    #+#             */
/*   Updated: 2021/03/17 15:43:08 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (c);
		i++;
	}
	return (0);
}

int	handle_map_check_valid(t_cub *s_cub)
{
	int	row;
	int	col;
	int	player_onset;

	player_onset = 0;
	row = 0;
	while (s_cub->map[row])
	{
		col = 0;
		while (s_cub->map[row][col])
		{
			if (!ft_in_set(s_cub->map[row][col], VALID_MAP_CHARACTERS))
				return (0);
			if (ft_in_set(s_cub->map[row][col], "NSWE"))
				player_onset += 1;
			col++;
		}
		row++;
	}
	if (player_onset != 1)
		return (0);
	return (1);
}

int	handle_map_left_right_borders(t_cub *s_cub)
{
	int	row;
	int	first;
	int	last;

	row = 0;
	while (s_cub->map[row])
	{
		first = 0;
		while (s_cub->map[row][first] == ' ')
			first++;
		last = ft_strlen(s_cub->map[row]) - 1;
		while (last > 0 && s_cub->map[row][last] == ' ')
			last--;
		if ((last - first) <= 1 || s_cub->map[row][first] != '1'
				|| s_cub->map[row][last] != '1')
			return (0);
		row++;
	}
	return (row);
}

int	handle_file_check_nswesrfc(t_cub *s_cub)
{
	if (!s_cub->no || !s_cub->so || !s_cub->we || !s_cub->ea ||
			!s_cub->sprite || !s_cub->r[0] || !s_cub->r[1] ||
			(s_cub->f[0] < 0 || s_cub->f[0] > 255) ||
			(s_cub->f[1] < 0 || s_cub->f[1] > 255) ||
			(s_cub->f[2] < 0 || s_cub->f[2] > 255) ||
			(s_cub->c[0] < 0 || s_cub->c[0] > 255) ||
			(s_cub->c[1] < 0 || s_cub->c[1] > 255) ||
			(s_cub->c[2] < 0 || s_cub->c[2] > 255))
		return (0);
	return (1);
}


int	handle_is_map_file_error(t_cub *s_cub)
{
	int	map_rows;

	if (!handle_file_check_nswesrfc(s_cub))
		return (1);
	printf("handle1\n");
	if (!handle_map_check_valid(s_cub))
		return (1);
	printf("handle2\n");
	if ((map_rows = handle_map_left_right_borders(s_cub)) <= 2)
		return (1);
	printf("handle3\n");
	if (s_cub->cols <= 2)
		return (1);
	return (0);
}
