/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 20:04:21 by mkal              #+#    #+#             */
/*   Updated: 2021/03/13 11:33:30 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	fire_rays(t_cub *s_cub)
{
	int	ray_idx;
	double	cameraX;
	static	int	memory_alloc = 1;

	if (memory_alloc)
	{
		s_cub->ray = malloc(sizeof(double[12]) * s_cub->r[0]);
		memory_alloc = 0;
	}
	ray_idx = -1;
	while (++ray_idx < s_cub->r[0])
	{
		//각각의 컬럼(ray_idx)에 대해서 -1부터 1까지의 값을 갖게 된다.
		cameraX = 2 * ray_idx / (double)s_cub->r[0] - 1;

		//ray[0], ray[1] = ray vector
		s_cub->ray[ray_idx][0] = s_cub->forward[0] + s_cub->plane[0] * cameraX;
		s_cub->ray[ray_idx][1] = s_cub->forward[1] + s_cub->plane[1] * cameraX;

		//ray[2], ray[3] = deltaDistX, deltaDistY
		s_cub->ray[ray_idx][2] = fabs(1 / s_cub->ray[ray_idx][0]);
		s_cub->ray[ray_idx][3] = fabs(1 / s_cub->ray[ray_idx][1]);

		int mapX = (int)s_cub->pos[0];
		int mapY = (int)s_cub->pos[1] + 1;
		int stepX;
		int stepY;

		//ray[4], ray[5] = sideDistX, sideDistY
		if (s_cub->ray[ray_idx][0] < 0)
		{
			stepX = -1;
			s_cub->ray[ray_idx][4] = (s_cub->pos[0] - mapX) * s_cub->ray[ray_idx][2];
		}
		else
		{
			stepX = 1;
			s_cub->ray[ray_idx][4] = (mapX + 1.0 - s_cub->pos[0]) * s_cub->ray[ray_idx][2];
		}
		if (s_cub->ray[ray_idx][1] < 0)
		{
			stepY = -1;
			s_cub->ray[ray_idx][5] = (s_cub->pos[1] - mapY) * s_cub->ray[ray_idx][3];
		}
		else
		{
			stepY = 1;
			s_cub->ray[ray_idx][5] = (mapY + 1.0 - s_cub->pos[1]) * s_cub->ray[ray_idx][3];
		}

		//perform DDA
		//ray[6] = distance
		int hit = 0;
		int side;
		while (hit == 0)
		{
			if (s_cub->ray[ray_idx][4] < s_cub->ray[ray_idx][5])
			{
				s_cub->ray[ray_idx][4] += s_cub->ray[ray_idx][2];
				mapX += stepX;
				side = 0;
			}
			else
			{
				s_cub->ray[ray_idx][5] += s_cub->ray[ray_idx][3];
				mapY += stepY;
				side = 1;
			}
			if (s_cub->map[mapX][mapY] == '1')
				hit = 1;
		}

		//ray[6] = distance
		//ray[7] 동(4)서(3)남(2)북(1), 위치는 상대적.
		if (side == 0)
		{
			//현재 맵은 왼쪽 상단에서부터 0,0으로 증가하기 때문에 플레이어가
			//N으로 북쪽을 보고 있음에도 (-1, 0)으로 표기되어 마치 좌표평면은
			//90도로 돌린것과 같은 모양새이다.
			//따라서 좌표평면을 중신으로 x방향 즉, horizontal 교차점을 가지는 것은 
			//결국에는 플레이어 시야 입장에서는 위아래, 북쪽과 남쪽을 가리키는 것이라고 할 수 있다.
			s_cub->ray[ray_idx][6] = (mapX - s_cub->pos[0] + (1 - stepX) / 2) /
				s_cub->ray[ray_idx][0];
			if (s_cub->ray[ray_idx][0] < 0)
				s_cub->ray[ray_idx][7] = 1; //북쪽
			else if (s_cub->ray[ray_idx][0] > 0)
				s_cub->ray[ray_idx][7] = 2;//남쪽
		}
		else	
		{
			s_cub->ray[ray_idx][6] = (mapY - s_cub->pos[1] + (1 - stepY) / 2) /
				s_cub->ray[ray_idx][1];
			if (s_cub->ray[ray_idx][1] < 0)
				s_cub->ray[ray_idx][7] = 3;
			else if (s_cub->ray[ray_idx][1] > 0)
				s_cub->ray[ray_idx][7] = 4;
			double tri_base = fabs(mapX - s_cub->pos[0]);
			double tri_height = sqrt((s_cub->ray[ray_idx][5] * s_cub->ray[ray_idx][5]) - tri_base * tri_base);
			s_cub->ray[ray_idx][8] = fabs((double)(mapY) - ((double)s_cub->pos[1] + tri_height));
			printf("tri : %g, tri_height : %g, ray8 : %g\n", tri_base, s_cub->ray[ray_idx][4], s_cub->ray[ray_idx][8]);
		}
		
		int lineHeight = (int)(s_cub->r[1] / s_cub->ray[ray_idx][6]);
		int drawStart = -lineHeight / 2 + s_cub->r[1] / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + s_cub->r[1] / 2;
		if (drawEnd >= s_cub->r[1])
			drawEnd = s_cub->r[1] - 1;

		int row_idx = -1;
		while (++row_idx < s_cub->r[1])
		{
			if (row_idx >= drawStart && row_idx < drawEnd)
			{
				if (s_cub->ray[ray_idx][7] == 4)
				{
					int x_perc = (int)(s_cub->ray[ray_idx][8] * (*s_cub->e->width));
					int idx = (row_idx % (*s_cub->e->height)) * (*s_cub->e->width) + (ray_idx % x_perc);
					s_cub->screen->data[row_idx * s_cub->r[0] + ray_idx] =
						s_cub->e->data[idx];
				}
				else if (s_cub->ray[ray_idx][7] == 3)
				{
					int idx = (row_idx % (*s_cub->w->height) * (*s_cub->w->width)) + (ray_idx % (*s_cub->w->width));
					s_cub->screen->data[row_idx * s_cub->r[0] + ray_idx] =
						s_cub->w->data[idx];
				}
				else if (s_cub->ray[ray_idx][7] == 2)
				{
					int idx = (row_idx % (*s_cub->s->height))
						* (*s_cub->s->width) + (ray_idx % (*s_cub->s->width));
					s_cub->screen->data[row_idx * s_cub->r[0] + ray_idx] =
						s_cub->s->data[idx];
				}
				else if (s_cub->ray[ray_idx][7] == 1)
				{
					int idx = (row_idx % (*s_cub->n->height))
						* (*s_cub->n->width) + (ray_idx % (*s_cub->n->width));
					s_cub->screen->data[row_idx * s_cub->r[0] + ray_idx] =
						s_cub->n->data[idx];
				}
			}
		}
	}
}


/*void	find_o_directions(t_cub *s_cub)
{
	s_cub->left[0] = s_cub->forward[0] * cos((double)1 / 2 * M_PI)
		- s_cub->forward[1] * sin((double)1 / 2 * M_PI);
	s_cub->left[1] = s_cub->forward[0] * sin((double)1 / 2 * M_PI)
		+ s_cub->forward[1] * cos((double)1 / 2 * M_PI);
	s_cub->backward[0] = s_cub->left[0] * cos((double)1 / 2 * M_PI)
		- s_cub->left[1] * sin((double)1 / 2 * M_PI);
	s_cub->backward[1] = s_cub->left[0] * sin((double)1 / 2 * M_PI)
		+ s_cub->left[1] * cos((double)1 / 2 * M_PI);
	s_cub->right[0] = s_cub->backward[0] * cos((double)1 / 2 * M_PI)
		- s_cub->backward[1] * sin((double)1 / 2 * M_PI);
	s_cub->right[1] = s_cub->backward[0] * sin((double)1 / 2 * M_PI)
		+ s_cub->backward[1] * cos((double)1 / 2 * M_PI);
}*/

//dirX = forward[0], dirY=forward[1]
void	find_direction(t_cub *s_cub, char c)
{
	if (c == 'N')
	{
		s_cub->forward[0] = -1;
		s_cub->forward[1] = 0;
		s_cub->plane[0] = 0;
		s_cub->plane[1] = 0.66;
	}
	else if (c == 'S')
	{
		s_cub->forward[0] = 1;
		s_cub->forward[1] = 0;
		s_cub->plane[0] = 0;
		s_cub->plane[1] = 0.66;
	}
	else if (c == 'E')
	{
		s_cub->forward[0] = 0;
		s_cub->forward[1] = 1;
		s_cub->plane[0] = 0.66;
		s_cub->plane[1] = 0;
	}
	else if (c == 'W')
	{
		s_cub->forward[0] = 0;
		s_cub->forward[1] = -1;
		s_cub->plane[0] = 0.66;
		s_cub->plane[1] = 0;
	}
}

void	find_start(t_cub *s_cub)
{
	int	row;
	int	col;

	row = 0;
	while (row < s_cub->lines)
	{
		col = 0;
		while (s_cub->map[row][col])
		{
			if (s_cub->map[row][col] == 'N' ||
					s_cub->map[row][col] == 'S' ||
					s_cub->map[row][col] == 'W' ||
					s_cub->map[row][col] == 'E')
			{
				s_cub->pos[0] = row + 0.5;
				s_cub->pos[1] = col + 0.5;
				find_direction(s_cub, s_cub->map[row][col]);
				break;
			}
			col++;
		}
		row++;
	}
}

void	game_init(t_cub *s_cub)
{
	find_start(s_cub);
	fire_rays(s_cub);
}
