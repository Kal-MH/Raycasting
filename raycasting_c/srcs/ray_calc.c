/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:45:13 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:45:16 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		iswall2(double *ray, char **map, double *pos, char object)
{
	int	coor[2];
	int	ret;

	ret = 0;
	if (ray[2] == floor(ray[2]) || (ray[2] > 0.99999 && ray[2] < 1.00001))
	{
		coor[0] = ray[2] > 0.99999 && ray[2] < 1.00001 ? 1 : ray[2];
		coor[1] = floor(ray[3]);
		if (map[coor[0]][coor[1]] == object)
			ret = sprite_calc(ray, pos, coor, 10 + object - '0');
		if (map[--coor[0]][coor[1]] == object)
			ret = sprite_calc(ray, pos, coor, 20 + object - '0');
	}
	else if (ray[3] == floor(ray[3]))
	{
		coor[0] = floor(ray[2]);
		coor[1] = ray[3];
		if (map[coor[0]][coor[1]] == object)
			ret = sprite_calc(ray, pos, coor, 30 + object - '0');
		if (map[coor[0]][--coor[1]] == object)
			ret = sprite_calc(ray, pos, coor, 40 + object - '0');
	}
	ret = object == '2' && ret > 0 ? 1 : ret;
	return (ret);
}

void	iswall(double *ray, char **map, double *pos)
{
	int	itswall;

	if ((itswall = iswall2(ray, map, pos, '1')))
	{
		ray[4] = ray[2];
		ray[5] = ray[3];
		ray[6] = itswall;
	}
	if (ray[6] == 3)
		ray[8] = fabs(floor(ray[4]) - ray[4]);
	else if (ray[6] == 2)
		ray[8] = fabs(ray[5] - floor(ray[5]));
	else if (ray[6] == 4)
		ray[8] = fabs(ceil(ray[4]) - ray[4]);
	else if (ray[6] == 1)
		ray[8] = fabs(ceil(ray[5]) - ray[5]);
	if (ray[9] == 0)
		ray[9] = iswall2(ray, map, pos, '2');
}

void	next_point(double a, char **map, double *pos, double *ray)
{
	ray[2] = ray[2] + ray[0] * a;
	ray[3] = ray[3] + ray[1] * a;
	iswall(ray, map, pos);
}

void	first_point(char **map, double *pos, double *ray)
{
	double	a;
	double	b;
	double	res;

	if (ray[0] != 0)
	{
		if (floor(ray[2]) == ray[2])
			a = fabs(1 / ray[0]);
		else
			a = ((ray[0] < 0 ? floor(ray[2]) : ceil(ray[2])) - ray[2]) / ray[0];
	}
	if (ray[1] != 0)
	{
		if (floor(ray[3]) == ray[3])
			b = fabs(1 / ray[1]);
		else
			b = ((ray[1] < 0 ? floor(ray[3]) : ceil(ray[3])) - ray[3]) / ray[1];
	}
	res = ray[0] == 0 ? b : a;
	if (ray[0] != 0 && ray[1] != 0)
		res = a < b ? a : b;
	next_point(res, map, pos, ray);
}

void	ray_calc(t_cub *s_cub)
{
	int	idx;

	idx = 0;
	while (idx < s_cub->r[0])
	{
		s_cub->ray[idx][2] = s_cub->pos[0];
		s_cub->ray[idx][3] = s_cub->pos[1];
		s_cub->ray[idx][6] = 0;
		s_cub->ray[idx][9] = 0;
		while (s_cub->ray[idx][6] == 0)
			first_point(s_cub->map, s_cub->pos, s_cub->ray[idx]);
		s_cub->ray[idx][7] = hypot(fabs(s_cub->ray[idx][4] -
			s_cub->pos[0]), fabs(s_cub->ray[idx][5] - s_cub->pos[1])) *
			sin(acos(s_cub->ray[idx][0] * s_cub->right[0] +
					s_cub->ray[idx][1] * s_cub->right[1]));
		idx++;
	}
}
