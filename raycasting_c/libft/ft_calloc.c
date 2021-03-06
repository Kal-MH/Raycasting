/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:02:39 by mkal              #+#    #+#             */
/*   Updated: 2020/10/05 15:06:28 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*addr;

	if (!(addr = malloc(nmemb * size)))
		return (0);
	ft_bzero(addr, nmemb * size);
	return (addr);
}
