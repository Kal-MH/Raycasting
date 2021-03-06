/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:44:14 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:44:27 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	memory_alloc_images(t_cub *s_cub)
{
	s_cub->n = malloc(sizeof(t_img));
	s_cub->s = malloc(sizeof(t_img));
	s_cub->e = malloc(sizeof(t_img));
	s_cub->w = malloc(sizeof(t_img));
	s_cub->sp = malloc(sizeof(t_img));
	s_cub->screen = malloc(sizeof(t_img));
	s_cub->n->width = malloc(sizeof(int));
	s_cub->n->height = malloc(sizeof(int));
	s_cub->s->width = malloc(sizeof(int));
	s_cub->s->height = malloc(sizeof(int));
	s_cub->e->width = malloc(sizeof(int));
	s_cub->e->height = malloc(sizeof(int));
	s_cub->w->width = malloc(sizeof(int));
	s_cub->w->height = malloc(sizeof(int));
	s_cub->sp->width = malloc(sizeof(int));
	s_cub->sp->height = malloc(sizeof(int));
	s_cub->sky_width = malloc(sizeof(int));
	s_cub->sky_height = malloc(sizeof(int));
	s_cub->grass_width = malloc(sizeof(int));
	s_cub->grass_height = malloc(sizeof(int));
}

void	get_img_data(t_cub *s_cub)
{
	s_cub->screen->data = (int *)mlx_get_data_addr(s_cub->screen->img_ptr,
		&s_cub->screen->bpp, &s_cub->screen->size_l, &s_cub->screen->endian);
	s_cub->n->data = (int *)mlx_get_data_addr(s_cub->n->img_ptr,
		&s_cub->n->bpp, &s_cub->n->size_l, &s_cub->n->endian);
	s_cub->s->data = (int *)mlx_get_data_addr(s_cub->s->img_ptr,
		&s_cub->s->bpp, &s_cub->s->size_l, &s_cub->s->endian);
	s_cub->e->data = (int *)mlx_get_data_addr(s_cub->e->img_ptr,
		&s_cub->e->bpp, &s_cub->e->size_l, &s_cub->e->endian);
	s_cub->w->data = (int *)mlx_get_data_addr(s_cub->w->img_ptr,
		&s_cub->w->bpp, &s_cub->w->size_l, &s_cub->w->endian);
	s_cub->sp->data = (int *)mlx_get_data_addr(s_cub->sp->img_ptr,
		&s_cub->sp->bpp, &s_cub->sp->size_l, &s_cub->sp->endian);
	free(s_cub->no);
	free(s_cub->so);
	free(s_cub->ea);
	free(s_cub->we);
	free(s_cub->sprite);
}

void	get_img_ptrs(t_cub *s_cub)
{
	s_cub->screen->img_ptr = mlx_new_image(s_cub->mlx,
		s_cub->r[0], s_cub->r[1]);
	s_cub->n->img_ptr = mlx_xpm_file_to_image(s_cub->mlx,
		s_cub->no, s_cub->n->width, s_cub->n->height);
	s_cub->s->img_ptr = mlx_xpm_file_to_image(s_cub->mlx,
		s_cub->so, s_cub->s->width, s_cub->s->height);
	s_cub->e->img_ptr = mlx_xpm_file_to_image(s_cub->mlx,
		s_cub->ea, s_cub->e->width, s_cub->e->height);
	s_cub->w->img_ptr = mlx_xpm_file_to_image(s_cub->mlx,
		s_cub->we, s_cub->w->width, s_cub->w->height);
	s_cub->sp->img_ptr = mlx_xpm_file_to_image(s_cub->mlx,
		s_cub->sprite, s_cub->sp->width, s_cub->sp->height);
	s_cub->sky = mlx_xpm_file_to_image(s_cub->mlx,
		"./textures/sky.xpm", s_cub->sky_width, s_cub->sky_height);
	s_cub->grass = mlx_xpm_file_to_image(s_cub->mlx,
		"./textures/grass.xpm", s_cub->grass_width,
		s_cub->grass_height);
}

void	load_images(t_cub *s_cub)
{
	memory_alloc_images(s_cub);
	get_img_ptrs(s_cub);
	get_img_data(s_cub);
}
