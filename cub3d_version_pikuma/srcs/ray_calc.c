/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:10:32 by mkal              #+#    #+#             */
/*   Updated: 2021/03/18 00:16:52 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	normalize_angle(double angle)
{
	angle = (angle - TWO_PI * (int)(angle / TWO_PI));
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

double distance_between_points(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	cast_ray(t_cub *s_cub, double ray_angle, int strip_id)
{
	ray_angle = normalize_angle(ray_angle);

	int	is_ray_facing_up = ray_angle > 0.5 * PI && ray_angle < 1.5 * PI;;
	int	is_ray_facing_down = !is_ray_facing_up;

	int	is_ray_facing_right = ray_angle > 0 && ray_angle < PI;
	int	is_ray_facing_left = !is_ray_facing_right;

	double	x_intercept, y_intercept;
	double	x_step, y_step;

	int	found_horz_wall_hit = 0;
	double	horz_wall_hit_x = 0;
	double	horz_wall_hit_y = 0;
	int	horz_wall_content = 0;

	y_intercept = floor(s_cub->player->x / TILE_SIZE) * TILE_SIZE;
	y_intercept += is_ray_facing_down ? TILE_SIZE : 0;

	x_intercept = s_cub->player->y + (y_intercept - s_cub->player->x) / tan(ray_angle);

	y_step = TILE_SIZE;
	y_step *= is_ray_facing_up ? -1 : 1;
	x_step = TILE_SIZE / tan(ray_angle);
	x_step *= (is_ray_facing_left && x_step > 0) ? -1 : 1;
	x_step *= (is_ray_facing_right && x_step < 0) ? -1 : 1;

	double	next_horz_touch_x = x_intercept;
	double	next_horz_touch_y = y_intercept;

	double	x_to_check = 0;
	double	y_to_check = 0;
	while (next_horz_touch_x >= 0 && next_horz_touch_x <= s_cub->r[1]
			&& next_horz_touch_y >= 0 && next_horz_touch_y <= s_cub->r[0])
	{
		x_to_check = next_horz_touch_x;
		y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 0);

		if (map_has_wall_at(s_cub, y_to_check, x_to_check))
		{
			y_to_check = y_to_check < 0 ? 0 : y_to_check;
			x_to_check = x_to_check < 0 ? 0 : x_to_check;
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			horz_wall_content = s_cub->map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			found_horz_wall_hit = 1;
			break ;
		}
		else
		{
			next_horz_touch_x += x_step;
			next_horz_touch_y += y_step;
		}
	}

	int	found_vert_wall_hit = 0;
	double	vert_wall_hit_x = 0;
	double	vert_wall_hit_y = 0;
	int	vert_wall_content = 0;

	x_intercept = floor(s_cub->player->y / TILE_SIZE) * TILE_SIZE;
	x_intercept += is_ray_facing_right ? TILE_SIZE : 0;

	y_intercept = s_cub->player->x - (x_intercept - s_cub->player->y) * tan(ray_angle);

	x_step = TILE_SIZE;
	x_step *= is_ray_facing_left ? -1 : 1;
	y_step = TILE_SIZE * tan(ray_angle);
	y_step *= (is_ray_facing_up && y_step > 0) ? -1 : 1;
	y_step *= (is_ray_facing_down && y_step < 0) ? -1 : 1;

	double	next_vert_touch_x = x_intercept;
	double	next_vert_touch_y = y_intercept;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= s_cub->r[1]
			&& next_vert_touch_y >= 0 && next_vert_touch_y <= s_cub->r[0])
	{
		x_to_check = next_vert_touch_x + (is_ray_facing_left ? -1 : 0);
		y_to_check = next_vert_touch_y;

		if (map_has_wall_at(s_cub, y_to_check, x_to_check))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			vert_wall_content = s_cub->map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			found_vert_wall_hit = 1;
			break ;
		}
		else
		{
			next_vert_touch_x += x_step;
			next_vert_touch_y += y_step;
		}
	}

	//printf("yi : %g, xi : %g\n", y_intercept, x_intercept);
	//printf("ys : %g, xs : %g\n", y_step, x_step);
	//printf("%g %g %c\n", vert_wall_hit_y, vert_wall_hit_x, vert_wall_content);

	double	horz_hit_distance = found_horz_wall_hit ?
		distance_between_points(s_cub->player->x, s_cub->player->y,
				horz_wall_hit_x, horz_wall_hit_y)
		: FLT_MAX;
	double	vert_hit_distance = found_vert_wall_hit ?
		distance_between_points(s_cub->player->x, s_cub->player->y,
				vert_wall_hit_x, vert_wall_hit_y)
		: FLT_MAX;

	if (vert_hit_distance < horz_hit_distance)
	{
		s_cub->rays[strip_id].distance = vert_hit_distance;
		s_cub->rays[strip_id].wall_hit_x = vert_wall_hit_x;
		s_cub->rays[strip_id].wall_hit_y = vert_wall_hit_y;
		s_cub->rays[strip_id].wall_hit_content = vert_wall_content;
		s_cub->rays[strip_id].was_hit_vertical = 1;
	}
	else
	{
		s_cub->rays[strip_id].distance = horz_hit_distance;
		s_cub->rays[strip_id].wall_hit_x = horz_wall_hit_x;
		s_cub->rays[strip_id].wall_hit_y = horz_wall_hit_y;
		s_cub->rays[strip_id].wall_hit_content = horz_wall_content;
		s_cub->rays[strip_id].was_hit_vertical = 0;
	}
	/*printf("%g %g %g %c %d\n", s_cub->rays[strip_id].distance, s_cub->rays[strip_id].wall_hit_x, s_cub->rays[strip_id].wall_hit_y, s_cub->rays[strip_id].wall_hit_content, s_cub->rays[strip_id].was_hit_vertical);
	*/
	s_cub->rays[strip_id].ray_angle = ray_angle;
	s_cub->rays[strip_id].is_ray_facing_down = is_ray_facing_down;
	s_cub->rays[strip_id].is_ray_facing_up = is_ray_facing_up;
	s_cub->rays[strip_id].is_ray_facing_left = is_ray_facing_left;
	s_cub->rays[strip_id].is_ray_facing_right = is_ray_facing_right;
}

void	cast_all_rays(t_cub *s_cub) {
	double	ray_angle;
	int	i;
	
	ray_angle = s_cub->player->rotation_angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < s_cub->r[0])
	{
		cast_ray(s_cub, ray_angle, i);
		ray_angle += FOV_ANGLE / s_cub->r[0];
		i++;
	}
}
