/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:45:29 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:45:32 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_bmph	get_header(t_cub *s_cub)
{
	int		height;
	int		width;
	t_bmph	bmph;

	width = s_cub->r[0];
	height = s_cub->r[1];
	bmph.id1 = 'B';
	bmph.id2 = 'M';
	bmph.bmp_file_size = 54 + 4 * width * height;
	bmph.reserved1 = 0;
	bmph.reserved2 = 0;
	bmph.offset = 54;
	bmph.dib = 40;
	bmph.width = width;
	bmph.height = -height;
	bmph.plane = 1;
	bmph.bpp = 32;
	bmph.compression = 0;
	bmph.raw_bitmap_size = 4 * width * height;
	bmph.resx = width;
	bmph.resy = height;
	bmph.number_of_colors = 0xffffff;
	bmph.important_colors = 0;
	return (bmph);
}

void	save_bmp(t_cub *s_cub)
{
	t_bmph	bmph;
	int		fd;

	fd = open("cub3d.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	bmph = get_header(s_cub);
	write(fd, &bmph, 54);
	write(fd, s_cub->screen->data, bmph.raw_bitmap_size);
	write(1, "cub.bmp file has been saved\n", 28);
	close(fd);
}
