/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:43:56 by mkal              #+#    #+#             */
/*   Updated: 2020/10/07 02:23:16 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h_len;
	size_t	n_len;
	size_t	size;

	if (!*needle)
		return ((char*)haystack);
	h_len = ft_strlen(haystack);
	n_len = ft_strlen(needle);
	if (h_len < n_len || len < n_len)
		return (0);
	size = (h_len > len) ? len : h_len;
	while (size-- >= n_len)
	{
		if (ft_memcmp(haystack, needle, n_len) == 0)
			return ((char*)haystack);
		haystack++;
	}
	return (0);
}
