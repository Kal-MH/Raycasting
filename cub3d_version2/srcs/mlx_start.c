/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:26:22 by mkal              #+#    #+#             */
/*   Updated: 2021/03/13 11:25:29 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
void	handle_movement(int keycode, t_cub *s_cub)
{
	if (keycode == KEY_W)
	{
		s_cub->pos[0] += s_cub->forward[0] * M_SPD;
		s_cub->pos[1] += s_cub->forward[1] * M_SPD;
	}
	else if (keycode == KEY_S)
	{
		s_cub->pos[0] -= s_cub->forward[0] * M_SPD;
		s_cub->pos[1] -= s_cub->forward[1] * M_SPD;
	}
}

int	key_press(int keycode, t_cub *s_cub)
{
	if (keycode == KEY_W || keycode == KEY_A)
		handle_movement(keycode, s_cub);
	else if (keycode == KEY_ESC)
		close_the_window(s_cub);
	draw_background(s_cub);
	fire_rays(s_cub);
	mlx_put_image_to_window(s_cub->mlx, s_cub->win, s_cub->screen->img_ptr, 0, 0);
	return (0);
}

void	mlx_start(t_cub *s_cub)
{
	mlx_hook(s_cub->win, KEY_PRESS, 0, &key_press, s_cub);
	mlx_hook(s_cub->win, KEY_DESTROY, 0, &close_the_window, s_cub);
	mlx_loop(s_cub->mlx);
}
