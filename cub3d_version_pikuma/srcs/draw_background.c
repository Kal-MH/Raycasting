/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:36:51 by mkal              #+#    #+#             */
/*   Updated: 2021/03/15 17:55:42 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_background(t_cub *s_cub)
{
	int	idx_row;
	int	idx_col;
	int	half_row;
	double	brightness;

	idx_row = -1;
	half_row = s_cub->r[1] / 2;
	while (++idx_row < s_cub->r[1])
	{
		brightness = fabs(((double)idx_row - half_row) / half_row);
		idx_col = -1;
		while (++idx_col < s_cub->r[0])
		{
			if (idx_row < half_row)
				s_cub->screen->data[idx_row * s_cub->r[0] + idx_col] =
					(int)(s_cub->c[0] * brightness) * 0x0010000 +
					(int)(s_cub->c[1] * brightness) * 0x0000100 +
					(int)(s_cub->c[2] * brightness);
			else
				s_cub->screen->data[idx_row * s_cub->r[0] + idx_col] =
					(int)(s_cub->f[0] * brightness) * 0x0010000 +
					(int)(s_cub->f[1] * brightness) * 0x0000100 +
					(int)(s_cub->f[2] * brightness);
		}
	}
}
