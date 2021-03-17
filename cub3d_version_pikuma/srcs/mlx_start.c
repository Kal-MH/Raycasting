/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:26:22 by mkal              #+#    #+#             */
/*   Updated: 2021/03/18 00:03:34 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	map_has_wall_at(t_cub *s_cub, double x, double y)
{
	int	map_grid_x;
	int	map_grid_y;

	if (x < 0 || x > s_cub->lines || y < 0 || y > s_cub->cols)
		return (1);
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	return (s_cub->map[map_grid_x][map_grid_y] == '1' ? 1 : 0);
}

void	move_player(t_cub *s_cub) {
	double	move_step;
	double	new_player_x;
	double	new_player_y;

	move_step = s_cub->player->walk_direction * s_cub->player->walk_speed;
	new_player_x = s_cub->player->x + cos(s_cub->player->rotation_angle) * move_step;
	new_player_y = s_cub->player->y + sin(s_cub->player->rotation_angle) * move_step;
	if (!map_has_wall_at(s_cub, new_player_x, new_player_y))
	{
		s_cub->player->x = new_player_x;
		s_cub->player->y = new_player_y;
	}
}

void	move_player_horizontal(int keycode, t_cub *s_cub)
{
	double	move_step;
	double	new_player_x;
	double	new_player_y;
	double	new_angle;

	new_angle = 0;
	move_step = s_cub->player->walk_direction * s_cub->player->walk_speed;
	new_angle = (keycode == KEY_A) ? s_cub->player->rotation_angle + (PI / 2) :
		s_cub->player->rotation_angle - (PI / 2);
	/*if (keycode == KEY_A)
		new_angle = s_cub->player->rotation_angle + (PI / 2);
	else 
		new_angle = s_cub->player->rotation_angle - (PI / 2);
	*/
	new_player_x = s_cub->player->x + cos(new_angle) * move_step;
	new_player_y = s_cub->player->y + sin(new_angle) * move_step;
	if (!map_has_wall_at(s_cub, new_player_x, new_player_y))
	{
		s_cub->player->x = new_player_x;
		s_cub->player->y = new_player_y;
	}
}

int	move_key_press_process(int keycode, t_cub *s_cub)
{
	if (keycode == KEY_W)
		s_cub->player->walk_direction = 1;
	else if (keycode == KEY_S)
		s_cub->player->walk_direction = -1;
	else if (keycode == KEY_A || keycode == KEY_D)
		s_cub->player->walk_direction = 1;
	else if (keycode == KEY_RIGHT)
	{
		s_cub->player->turn_direction = -1;
		s_cub->player->rotation_angle += s_cub->player->turn_direction *
			s_cub->player->turn_speed;
	}
	else if (keycode == KEY_LEFT)
	{
		s_cub->player->turn_direction = 1;
		s_cub->player->rotation_angle += s_cub->player->turn_direction *
			s_cub->player->turn_speed;
	}

	if (keycode == KEY_A || keycode == KEY_D)
		move_player_horizontal(keycode, s_cub);
	else
		move_player(s_cub);
	//render_map_player(s_cub);
	//mlx_put_image_to_window(s_cub->mlx, s_cub->win, s_cub->screen->img_ptr, 0, 0);
	return (0);
}

int	move_key_release_process(int keycode, t_cub *s_cub)
{
	if (keycode == KEY_W)
		s_cub->player->walk_direction = 0;
	else if (keycode == KEY_S)
		s_cub->player->walk_direction = 0;
	else if (keycode == KEY_A)
		s_cub->player->walk_direction = 0;
	else if (keycode == KEY_D)
		s_cub->player->walk_direction = 0;
	else if (keycode == KEY_LEFT)
		s_cub->player->turn_direction = 0;
	else if (keycode == KEY_RIGHT)
		s_cub->player->turn_direction = 0;

	return (0);
}

int	key_press(int keycode, t_cub *s_cub)
{
	if (keycode == KEY_ESC)
		close_the_window(s_cub);
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_RIGHT
			|| keycode == KEY_LEFT || keycode == KEY_A
			|| keycode == KEY_D)
		move_key_press_process(keycode, s_cub);
	return (0);
}

void	mlx_start(t_cub *s_cub)
{
	mlx_hook(s_cub->win, KEY_PRESS, 0, &key_press, s_cub);
	mlx_hook(s_cub->win, KEY_DESTROY, 0, &close_the_window, s_cub);
	mlx_hook(s_cub->win, KEY_RELEASE, 1L<<1, &move_key_release_process, s_cub);
	mlx_loop(s_cub->mlx);
}
