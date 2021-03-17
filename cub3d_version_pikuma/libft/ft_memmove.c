/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 01:26:56 by mkal              #+#    #+#             */
/*   Updated: 2020/10/07 01:46:23 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dst;
	char	*s;

	if (src < dest)
	{
		dst = (char*)dest;
		s = (char*)src;
		while (n--)
			dst[n] = s[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
