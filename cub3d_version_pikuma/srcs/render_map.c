/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:04:40 by mkal              #+#    #+#             */
/*   Updated: 2021/03/17 23:53:41 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	generate_3d_projection(t_cub *s_cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < s_cub->r[1])
	{
		double	perp_distance = s_cub->rays[i].distance * cos(s_cub->rays[i].ray_angle - s_cub->player->rotation_angle);
		double	distance_proj_plane = (s_cub->r[1] / 2) / tan(FOV_ANGLE / 2);
		double	projected_wall_height = (TILE_SIZE / perp_distance) * distance_proj_plane;

		int	wall_strip_height = (int)projected_wall_height;
		int	wall_top_pixel = (s_cub->r[0] / 2) - (wall_strip_height / 2);
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
		int	wall_bottom_pixel = (s_cub->r[0] / 2) + (wall_strip_height / 2);
		wall_bottom_pixel = wall_bottom_pixel > s_cub->r[0] ?
			s_cub->r[0] : wall_bottom_pixel;

		j = wall_top_pixel;
		while (j < wall_bottom_pixel)
		{
			s_cub->screen->data[(j * s_cub->r[1]) + i] = s_cub->rays[i].was_hit_vertical ? 0xffffff : 0xcccccc;
			j++;
		}
		i++;
	}
}

void	render_map(t_cub *s_cub)
{
	generate_3d_projection(s_cub);
}

