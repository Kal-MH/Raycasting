/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:53:28 by mkal              #+#    #+#             */
/*   Updated: 2021/02/25 16:17:42 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define OPEN_MAX 256

# define ONREAD 1
# define END 0
# define ERROR -1

# define NOT_FOUND -1

# define BUFFER_SIZE 16

int		get_next_line(int fd, char **line);

size_t	my_strlen(const char *s);

char	*my_strdup(char *s1);
char	*my_strjoin(char *s1, char *s2);

#endif
