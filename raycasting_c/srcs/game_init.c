/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:04:21 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:39:34 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	fire_rays(t_cub *s_cub)
{
	int			idx;
	double		r;
	static	int	memory_alloc = 1;

	if (memory_alloc)
	{
		s_cub->ray = malloc(sizeof(double[12]) * s_cub->r[0]);
		memory_alloc = 0;
	}
	idx = 0;
	//60 degree and divide with resolution x?
	r = M_PI / 3 / s_cub->r[0];
	while (idx < s_cub->r[0])
	{
		s_cub->ray[idx][0] = s_cub->forward[0] *
								cos((double)1 / 6 * M_PI - idx * r) -
								s_cub->forward[1] *
								sin((double)1 / 6 * M_PI - idx * r);
		s_cub->ray[idx][1] = s_cub->forward[0] *
								sin((double)1 / 6 * M_PI - idx * r) +
								s_cub->forward[1] *
								cos((double)1 / 6 * M_PI - idx * r);
		idx++;
	}
}


void	find_o_directions(t_cub *s_cub)
{
	s_cub->left[0] = s_cub->forward[0] * cos((double)1 / 2 * M_PI)
		- s_cub->forward[1] * sin((double)1 / 2 * M_PI);
	s_cub->left[1] = s_cub->forward[0] * sin((double)1 / 2 * M_PI)
		+ s_cub->forward[1] * cos((double)1 / 2 * M_PI);
	s_cub->backward[0] = s_cub->left[0] * cos((double)1 / 2 * M_PI)
		- s_cub->left[1] * sin((double)1 / 2 * M_PI);
	s_cub->backward[1] = s_cub->left[0] * sin((double)1 / 2 * M_PI)
		+ s_cub->left[1] * cos((double)1 / 2 * M_PI);
	s_cub->right[0] = s_cub->backward[0] * cos((double)1 / 2 * M_PI)
		- s_cub->backward[1] * sin((double)1 / 2 * M_PI);
	s_cub->right[1] = s_cub->backward[0] * sin((double)1 / 2 * M_PI)
		+ s_cub->backward[1] * cos((double)1 / 2 * M_PI);
}

void	find_direction(t_cub *s_cub, char c)
{
	if (c == 'N')
	{
		s_cub->forward[0] = -1;
		s_cub->forward[1] = 0;
	}
	else if (c == 'S')
	{
		s_cub->forward[0] = 1;
		s_cub->forward[1] = 0;
	}
	else if (c == 'E')
	{
		s_cub->forward[0] = 0;
		s_cub->forward[1] = 1;
	}
	else if (c == 'W')
	{
		s_cub->forward[0] = 0;
		s_cub->forward[1] = -1;
	}
}

void	find_start(t_cub *s_cub)
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
				s_cub->pos[0] = row + 0.5;
				s_cub->pos[1] = col + 0.5;
				find_direction(s_cub, s_cub->map[row][col]);
				break;
			}
			col++;
		}
		row++;
	}
}

void	game_init(t_cub *s_cub)
{
	find_start(s_cub);
	find_o_directions(s_cub);
	fire_rays(s_cub);
}
