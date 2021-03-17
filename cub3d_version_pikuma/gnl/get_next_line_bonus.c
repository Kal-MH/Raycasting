/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:07:22 by mkal              #+#    #+#             */
/*   Updated: 2020/11/25 15:11:59 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int	gnl_split_newline(char **stored_line, char **line, int newline)
{
	char	*temp;

	(*stored_line)[newline] = '\0';
	*line = ft_strdup(*stored_line);
	if ((*stored_line + newline + 1) == '\0')
	{
		free(*stored_line);
		*stored_line = 0;
		return (ONREAD);
	}
	temp = ft_strdup(*stored_line + newline + 1);
	free(*stored_line);
	*stored_line = temp;
	return (ONREAD);
}

int	gnl_finish_line(char **stored_line, char **line)
{
	int	newline;

	if (*stored_line && (newline = gnl_strchr_linebreak(*stored_line)) >= 0)
		return (gnl_split_newline(stored_line, line, newline));
	else if (*stored_line)
	{
		*line = *stored_line;
		*stored_line = 0;
		return (END);
	}
	*line = ft_strdup("");
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
	while ((n = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[n] = '\0';
		stored_line[fd] = ft_strjoin(stored_line[fd], buf);
		if ((newline = gnl_strchr_linebreak(stored_line[fd])) >= 0)
		{
			free(buf);
			return (gnl_split_newline(&stored_line[fd], line, newline));
		}
	}
	if (n < 0)
		return (ERROR);
	free(buf);
	return (gnl_finish_line(&stored_line[fd], line));
}
