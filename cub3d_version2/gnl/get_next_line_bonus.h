/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:53:28 by mkal              #+#    #+#             */
/*   Updated: 2020/11/25 15:12:14 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define OPEN_MAX 256

# define ONREAD 1
# define END 0
# define ERROR -1

# define NOT_FOUND -1

int		get_next_line(int fd, char **line);

size_t	ft_strlen(const char *s);

char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);

#endif
