/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 11:32:05 by mkal              #+#    #+#             */
/*   Updated: 2020/10/08 14:46:24 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static	char	*ft_malloc_word(char const *s, char c)
{
	char	*str;
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	if (!(str = (char *)malloc(len + 1)))
		return (0);
	len = 0;
	while (*s && *s != c)
		str[len++] = *s++;
	str[len] = 0;
	return (str);
}

void			*ft_free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

char			**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;

	if (!s)
		return (0);
	if (!(arr = (char **)malloc(sizeof(char*) * (count_words(s, c) + 1))))
		return (0);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(arr[i] = ft_malloc_word(s, c)))
				return (ft_free_arr(arr));
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	arr[i] = 0;
	return (arr);
}
