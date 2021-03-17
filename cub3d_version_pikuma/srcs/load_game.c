/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:13:10 by mkal              #+#    #+#             */
/*   Updated: 2021/03/17 15:00:02 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	memory_alloc_images_player(t_cub *s_cub)
{
	s_cub->player = malloc(sizeof(t_player));
	s_cub->screen = malloc(sizeof(t_img));
	s_cub->n = malloc(sizeof(t_img));
	s_cub->n->width = malloc(sizeof(int));
	s_cub->n->height = malloc(sizeof(int));
	s_cub->s = malloc(sizeof(t_img));
	s_cub->s->width = malloc(sizeof(int));
	s_cub->s->height = malloc(sizeof(int));
	s_cub->w = malloc(sizeof(t_img));
	s_cub->w->width = malloc(sizeof(int));
	s_cub->w->height = malloc(sizeof(int));
	s_cub->e = malloc(sizeof(t_img));
	s_cub->e->width = malloc(sizeof(int));
	s_cub->e->height = malloc(sizeof(int));

}

void	get_img_ptrs(t_cub *s_cub)
{
	s_cub->screen->img_ptr = mlx_new_image(s_cub->mlx,
			s_cub->r[0], s_cub->r[1]);
	s_cub->n->img_ptr = mlx_xpm_file_to_image(s_cub->mlx,
			s_cub->no, s_cub->n->width, s_cub->n->height);
	s_cub->s->img_ptr = mlx_xpm_file_to_image(s_cub->mlx,
			s_cub->so, s_cub->s->width, s_cub->s->height);
	s_cub->w->img_ptr = mlx_xpm_file_to_image(s_cub->mlx,
			s_cub->we, s_cub->w->width, s_cub->w->height);
	s_cub->e->img_ptr = mlx_xpm_file_to_image(s_cub->mlx,
			s_cub->ea, s_cub->e->width, s_cub->e->height);
}

void	get_img_data(t_cub *s_cub)
{
	s_cub->screen->data = (int*)mlx_get_data_addr(s_cub->screen->img_ptr,
			&s_cub->screen->bpp, &s_cub->screen->size_l, &s_cub->screen->endian);
	s_cub->n->data = (int*)mlx_get_data_addr(s_cub->n->img_ptr,
			&s_cub->n->bpp, &s_cub->n->size_l, &s_cub->n->endian);
	s_cub->s->data = (int*)mlx_get_data_addr(s_cub->s->img_ptr,
			&s_cub->s->bpp, &s_cub->s->size_l, &s_cub->s->endian);
	s_cub->w->data = (int*)mlx_get_data_addr(s_cub->w->img_ptr,
			&s_cub->w->bpp, &s_cub->w->size_l, &s_cub->w->endian);
	s_cub->e->data = (int*)mlx_get_data_addr(s_cub->e->img_ptr,
			&s_cub->e->bpp, &s_cub->e->size_l, &s_cub->e->endian);
}

void	load_game(t_cub *s_cub)
{
	memory_alloc_images_player(s_cub);
	get_img_ptrs(s_cub);
	get_img_data(s_cub);
	s_cub->rays = (t_ray*)malloc(sizeof(t_ray) * s_cub->r[1]);
}
