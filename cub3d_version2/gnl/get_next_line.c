/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:07:22 by mkal              #+#    #+#             */
/*   Updated: 2021/02/25 16:16:53 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strchr_linebreak(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (NOT_FOUND);
}

int	gnl_finish_line(char **stored_line, char **line, int newline)
{
	char	*temp;

	if (newline >= 0)
	{
		(*stored_line)[newline] = '\0';
		*line = my_strdup(*stored_line);
		temp = my_strdup(*stored_line + newline + 1);
		free(*stored_line);
		*stored_line = temp;
		return (ONREAD);
	}
	if (*stored_line)
	{
		*line = *stored_line;
		*stored_line = 0;
	}
	else
		*line = my_strdup("");
	return (END);
}

int	get_next_line(int fd, char **line)
{
	int			n;
	int			newline;
	char		*buf;
	static char	*stored_line[OPEN_MAX];

	if ((fd < 0 || fd > OPEN_MAX) || !line || BUFFER_SIZE <= 0
			|| !(buf = malloc(BUFFER_SIZE + 1)))
		return (ERROR);
	if (!stored_line[fd])
		stored_line[fd] = my_strdup("");
	while (!((newline = gnl_strchr_linebreak(stored_line[fd])) >= 0) &&
			((n = read(fd, buf, BUFFER_SIZE)) > 0))
	{
		buf[n] = '\0';
		if (stored_line[fd])
			stored_line[fd] = my_strjoin(stored_line[fd], buf);
		else
			stored_line[fd] = my_strdup(buf);
	}
	if (n == -1)
		return (ERROR);
	free(buf);
	return (gnl_finish_line(&stored_line[fd], line, newline));
}
