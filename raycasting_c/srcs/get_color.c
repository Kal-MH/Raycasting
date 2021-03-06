/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:43:56 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:44:06 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		get_color(int color, double distance)
{
	int r;
	int g;
	int b;
	int ret;

	r = color / 0x0010000;
	g = (color - r * 0x0010000) / 0x0000100;
	b = color - r * 0x0010000 - g * 0x0000100;
	if (distance > 1)
	{
		r = r / distance;
		g = g / distance;
		b = b / distance;
	}
	ret = r * 0x0010000 + g * 0x0000100 + b;
	return (ret);
}
