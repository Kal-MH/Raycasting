/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:43:28 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:43:44 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		get_width(t_cub *s_cub, int wall_num)
{
	if (wall_num == 1)
		return (*s_cub->n->width);
	else if (wall_num == 2)
		return (*s_cub->s->width);
	else if (wall_num == 3)
		return (*s_cub->w->width);
	else if (wall_num == 4)
		return (*s_cub->e->width);
	else if (wall_num == 5)
		return (*s_cub->sp->width);
	return (0);
}

int		get_height(t_cub *s_cub, int wall_num)
{
	if (wall_num == 1)
		return (*s_cub->n->height);
	else if (wall_num == 2)
		return (*s_cub->s->height);
	else if (wall_num == 3)
		return (*s_cub->w->height);
	else if (wall_num == 4)
		return (*s_cub->e->height);
	else if (wall_num == 5)
		return (*s_cub->sp->height);
	return (0);
}

void	draw_a_line(t_cub *s_cub, int ray_idx, int *wall_data)
{
	int		y_idx;
	double	scale_multiplier;
	int		range[2];
	int		idx;
	double	y_perc;

	y_idx = -1;
	scale_multiplier = s_cub->ray[ray_idx][7] < 0.01 ?
		100 : 1 / s_cub->ray[ray_idx][7];
	range[0] = (s_cub->r[1] / 2) - (s_cub->r[1] * scale_multiplier / 2);
	range[1] = (s_cub->r[1] / 2) + (s_cub->r[1] * scale_multiplier / 2);
	while (++y_idx < s_cub->r[1])
		if (y_idx >= range[0] && y_idx < range[1])
		{
			y_perc = ((double)y_idx - range[0]) / (range[1] - range[0]);
			idx = get_width(s_cub, s_cub->ray[ray_idx][6])
				* ((int)(y_perc * get_height(s_cub, s_cub->ray[ray_idx][6]))
				+ s_cub->ray[ray_idx][8]);
			s_cub->screen->data[y_idx * s_cub->r[0] + ray_idx] =
				get_color(wall_data[idx], s_cub->ray[ray_idx][7]);
		}
}

int		*get_which_wall(t_cub *s_cub, int ray_idx)
{
	if (s_cub->ray[ray_idx][6] == 1)
		return (s_cub->n->data);
	else if (s_cub->ray[ray_idx][6] == 2)
		return (s_cub->s->data);
	else if (s_cub->ray[ray_idx][6] == 3)
		return (s_cub->w->data);
	else if (s_cub->ray[ray_idx][6] == 4)
		return (s_cub->e->data);
	return (NULL);
}

void	draw_walls(t_cub *s_cub)
{
	int	ray_idx;
	int	*wall_data;

	ray_idx = 0;
	while (ray_idx < s_cub->r[0])
	{
		wall_data = get_which_wall(s_cub, ray_idx);
		draw_a_line(s_cub, ray_idx, wall_data);
		ray_idx++;
	}
}
