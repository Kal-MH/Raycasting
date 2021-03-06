/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:44:43 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:44:47 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	rotate(int keycode, t_cub *s_cub)
{
	double forward[2];

	forward[0] = s_cub->forward[0];
	forward[1] = s_cub->forward[1];
	if (keycode == KEY_LEFT)
	{
		s_cub->forward[0] = forward[0] * cos(0.1) -
							forward[1] * sin(0.1);
		s_cub->forward[1] = forward[0] * sin(0.1) +
							forward[1] * cos(0.1);
	}
	else if (keycode == KEY_RIGHT)
	{
		s_cub->forward[0] = forward[0] * cos(-0.1) -
							forward[1] * sin(-0.1);
		s_cub->forward[1] = forward[0] * sin(-0.1) +
							forward[1] * cos(-0.1);
	}
	else if (keycode == KEY_ESC)
		close_the_window(s_cub);
	find_o_directions(s_cub);
}

void	movement(int keycode, t_cub *s_cub)
{
	if (keycode == KEY_W && collision_check(keycode, s_cub))
	{
		s_cub->pos[0] += s_cub->forward[0] * M_SPD;
		s_cub->pos[1] += s_cub->forward[1] * M_SPD;
	}
	else if (keycode == KEY_A && collision_check(keycode, s_cub))
	{
		s_cub->pos[0] += s_cub->left[0] * M_SPD;
		s_cub->pos[1] += s_cub->left[1] * M_SPD;
	}
	else if (keycode == KEY_S && collision_check(keycode, s_cub))
	{
		s_cub->pos[0] += s_cub->backward[0] * M_SPD;
		s_cub->pos[1] += s_cub->backward[1] * M_SPD;
	}
	else if (keycode == KEY_D && collision_check(keycode, s_cub))
	{
		s_cub->pos[0] += s_cub->right[0] * M_SPD;
		s_cub->pos[1] += s_cub->right[1] * M_SPD;
	}
}

int		key_press(int keycode, t_cub *s_cub)
{
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S ||
			keycode == KEY_D)
		movement(keycode, s_cub);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_ESC)
		rotate(keycode, s_cub);
	fire_rays(s_cub);
	ray_calc(s_cub);
	draw_background(s_cub);
	draw_walls(s_cub);
	draw_sprite(s_cub);
	printf("y : %f x : %f diry : %f dirx : %f\n", s_cub->pos[0],
			s_cub->pos[1], s_cub->forward[0], s_cub->forward[1]);
	mlx_put_image_to_window(s_cub->mlx, s_cub->win,
		s_cub->screen->img_ptr, 0, 0);
	return (0);
}

void	mlx_start(t_cub *s_cub)
{
	mlx_hook(s_cub->win, 2, 0, &key_press, s_cub);
	mlx_hook(s_cub->win, 17, 0, &close_the_window, s_cub);
	mlx_loop(s_cub->mlx);
}
