/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:59:23 by mkal              #+#    #+#             */
/*   Updated: 2021/02/25 16:19:09 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	my_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*my_strdup(char *s1)
{
	char	*result;
	int		i;

	if (!(result = (char*)malloc(my_strlen(s1) + 1)))
		return (0);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*my_strjoin(char *s1, char *s2)
{
	char	*result;
	char	*temp;
	int		i;

	if (!(s1) && !(s2))
		return (0);
	if (!(s1) || !(s2))
		return (s1 ? my_strdup(s1) : my_strdup(s2));
	if (!(result = (char *)malloc(my_strlen(s1) + my_strlen(s2) + 1)))
		return (0);
	i = 0;
	temp = s1;
	while (*s1)
		result[i++] = *s1++;
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	free(temp);
	return (result);
}
