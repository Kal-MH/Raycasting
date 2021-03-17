/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:37:20 by mkal              #+#    #+#             */
/*   Updated: 2021/03/17 23:35:19 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	find_player_rotation_angle(t_cub *s_cub, int dir_char)
{
	if (dir_char == 'N')
		s_cub->player->rotation_angle = PI;
	else if (dir_char == 'E')
		s_cub->player->rotation_angle = PI / 2;
	else if (dir_char == 'S')
		s_cub->player->rotation_angle = 0;
	else if (dir_char == 'W')
		s_cub->player->rotation_angle = (3 * PI) / 2;
}

void	find_player_position(t_cub *s_cub)
{
	int	row;
	int	col;

	row = 0;
	while (row < s_cub->lines)
	{
		col = 0;
		while (s_cub->map[row][col])
		{
			if (s_cub->map[row][col] == 'N' ||
					s_cub->map[row][col] == 'S' ||
					s_cub->map[row][col] == 'W' ||
					s_cub->map[row][col] == 'E')
			{
				s_cub->player->x = row + 0.5;
				s_cub->player->y = col + 0.5;
				find_player_rotation_angle(s_cub, s_cub->map[row][col]);
			}
			col++;
		}
		row++;
	}
}

void	player_setup(t_cub *s_cub)
{
	find_player_position(s_cub);
	s_cub->player->turn_direction = 0;
	s_cub->player->walk_direction = 0;
	s_cub->player->walk_speed = 1;
	s_cub->player->turn_speed = 45 * (PI  / 180);
}

void	game_init(t_cub *s_cub)
{
	s_cub->num_of_rays = s_cub->r[1];
	player_setup(s_cub);
	cast_all_rays(s_cub);
	render_map(s_cub);
}
