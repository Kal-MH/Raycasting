/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_the_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 00:13:09 by mkal              #+#    #+#             */
/*   Updated: 2021/03/17 15:00:11 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map(t_cub *s_cub)
{
	int	idx;

	idx = -1;
	while (++idx < s_cub->lines)
		free(s_cub->map[idx]);
	free(s_cub->map);
}

void	free_images(t_cub *s_cub)
{
	free(s_cub->n->width);
	free(s_cub->n->height);
	free(s_cub->w->width);
	free(s_cub->w->height);
	free(s_cub->s->width);
	free(s_cub->s->height);
	free(s_cub->e->width);
	free(s_cub->e->height);
	free(s_cub->n);
	free(s_cub->w);
	free(s_cub->e);
	free(s_cub->s);
	free(s_cub->screen);
	free(s_cub->player);
}

int	close_the_window(t_cub *s_cub)
{
	mlx_destroy_image(s_cub->mlx, s_cub->screen->img_ptr);
	mlx_destroy_image(s_cub->mlx, s_cub->w->img_ptr);
	mlx_destroy_image(s_cub->mlx, s_cub->s->img_ptr);
	mlx_destroy_image(s_cub->mlx, s_cub->e->img_ptr);
	mlx_destroy_image(s_cub->mlx, s_cub->n->img_ptr);
	free_map(s_cub);
	free_images(s_cub);
	free(s_cub->rays);
	mlx_destroy_window(s_cub->mlx, s_cub->win);
	free(s_cub->mlx);
	exit(0);
	return (0);
}
