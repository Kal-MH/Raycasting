/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:45:46 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:45:48 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		sprite_calc(double *ray, double *pos, int *coor, int wall_num)
{
	double	vector_to_sp[2];
	double	max_theta;
	double	ray_theta;

	if (wall_num % 10 == 1)
		return (wall_num / 10);
	else if (wall_num % 10 == 2)
	{
		vector_to_sp[0] = (double)coor[0] + 0.5 - pos[0];
		vector_to_sp[1] = (double)coor[1] + 0.5 - pos[1];
		ray[10] = hypot(vector_to_sp[0], vector_to_sp[1]);
		max_theta = atan(1 / ray[10]);
		ray_theta = acos((ray[0] * vector_to_sp[0] + ray[1] * vector_to_sp[1])
					/ hypot(vector_to_sp[0], vector_to_sp[1]));
		ray[11] = 0.48 - ray_theta / max_theta;
		ray[11] = ray[11] < 0 ? 0 : ray[11];
		return (1);
	}
	return (0);
}
