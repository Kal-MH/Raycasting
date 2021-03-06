/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:43:08 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:43:17 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_sprite_line(t_cub *s_cub, int ray_idx, int *sprite_data)
{
	int		y_idx;
	double	scale_multiplier;
	int		range[2];
	int		idx;
	double	y_perc;

	y_idx = -1;
	scale_multiplier = s_cub->ray[ray_idx][10] < 0.01 ?
		50 : 0.5 / s_cub->ray[ray_idx][10];
	range[0] = (s_cub->r[1] / 2) - (s_cub->r[1] * scale_multiplier / 2);
	range[1] = (s_cub->r[1] / 2) + (s_cub->r[1] * scale_multiplier / 2);
	while (++y_idx < s_cub->r[1])
		if (y_idx >= range[0] && y_idx <= range[1])
		{
			y_perc = ((double)y_idx - range[0]) / (range[1] - range[0]);
			idx = get_width(s_cub, 5) * ((int)(y_perc
				* get_height(s_cub, 5)) + s_cub->ray[ray_idx][11]);
			if (sprite_data[idx] > 0x333333)
				s_cub->screen->data[y_idx * s_cub->r[0] + ray_idx] =
					sprite_data[idx];
		}
}

void	draw_sprite(t_cub *s_cub)
{
	int	ray_idx;

	ray_idx = -1;
	while (++ray_idx < s_cub->r[0])
		if (s_cub->ray[ray_idx][9])
			draw_sprite_line(s_cub, ray_idx, s_cub->sp->data);
}
