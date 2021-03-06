/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:42:22 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:42:33 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		can_i_go(int y, int x, char **map)
{
	if (map[y][x] == '1' || map[y][x] == '2')
		return (0);
	return (1);
}

int		collision_check(int keycode, t_cub *s_cub)
{
	double y;
	double x;

	if (keycode == KEY_W)
	{
		y = s_cub->pos[0] + s_cub->forward[0];
		x = s_cub->pos[1] + s_cub->forward[1];
	}
	if (keycode == KEY_A)
	{
		y = s_cub->pos[0] + s_cub->left[0];
		x = s_cub->pos[1] + s_cub->left[1];
	}
	if (keycode == KEY_S)
	{
		y = s_cub->pos[0] + s_cub->backward[0];
		x = s_cub->pos[1] + s_cub->backward[1];
	}
	if (keycode == KEY_D)
	{
		y = s_cub->pos[0] + s_cub->right[0];
		x = s_cub->pos[1] + s_cub->right[1];
	}
	return (can_i_go(y, x, s_cub->map));
}
