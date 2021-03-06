/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:42:50 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:42:56 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_background_texture(t_cub *s_cub)
{
	mlx_put_image_to_window(s_cub->mlx, s_cub->win, s_cub->sky, 0, 0);
	mlx_put_image_to_window(s_cub->mlx, s_cub->win, s_cub->grass, 0,
		s_cub->r[1] / 2);
}

void	draw_background(t_cub *s_cub)
{
	int		idx_y;
	int		idx_x;
	int		half_y;
	double	brightness;

	idx_y = -1;
	half_y = s_cub->r[1] / 2;
	while (++idx_y < s_cub->r[1])
	{
		brightness = fabs(((double)idx_y - half_y) / half_y);
		idx_x = -1;
		while (++idx_x < s_cub->r[0])
			if (idx_y < half_y)
			{
				s_cub->screen->data[idx_y * s_cub->r[0] + idx_x] =
					(int)(s_cub->c[0] * brightness) * 0x0010000 +
					(int)(s_cub->c[1] * brightness) * 0x0000100 +
					(int)(s_cub->c[2] * brightness);
			}
			else
				s_cub->screen->data[idx_y * s_cub->r[0] + idx_x] =
					(int)(s_cub->f[0] * brightness) * 0x0010000 +
					(int)(s_cub->f[1] * brightness) * 0x0000100 +
					(int)(s_cub->f[2] * brightness);
	}
}
