/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:53:38 by mkal              #+#    #+#             */
/*   Updated: 2021/03/02 20:24:46 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_resolution(char *line, t_cub *s_cub)
{
	s_cub->r[0] = ft_atoi(ft_strchr(line, ' '));
	s_cub->r[1] = ft_atoi(ft_strrchr(line, ' '));
	s_cub->r[0] = s_cub->r[0] > 5120 ? 5120 : s_cub->r[0];
	s_cub->r[1] = s_cub->r[1] > 2880 ? 2880 : s_cub->r[1];
}

void	put_floor_ceiling(char *line, t_cub *s_cub)
{
	if (ft_strchr(line, ',') != ft_strrchr(line, ','))
	{
		if (line[0] == 'F')
		{
			s_cub->f[0] = (double)ft_atoi(line + 2);
			s_cub->f[1] = (double)ft_atoi(ft_strchr(line, ',') + 1);
			s_cub->f[2] = (double)ft_atoi(ft_strrchr(line, ',') + 1);
		}
		else if (line[0] == 'C')
		{
			s_cub->c[0] = (double)ft_atoi(line + 2);
			s_cub->c[1] = (double)ft_atoi(ft_strchr(line, ',') + 1);
			s_cub->c[2] = (double)ft_atoi(ft_strrchr(line, ',') + 1);
		}
	}
}

char*	devide_path_index(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (line + i);
}

void	devide_spec_content(char *line, t_cub *s_cub)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		s_cub->no = ft_strdup(devide_path_index(line + 3));
	else if (ft_strncmp(line, "SO", 2) == 0)
		s_cub->so = ft_strdup(devide_path_index(line + 3));
	else if (ft_strncmp(line, "EA", 2) == 0)
		s_cub->ea = ft_strdup(devide_path_index(line + 3));
	else if (ft_strncmp(line, "WE", 2) == 0)
		s_cub->we = ft_strdup(devide_path_index(line + 3));
	else if (ft_strncmp(line, "S", 1) == 0)
		s_cub->sprite = ft_strdup(devide_path_index(line + 2));
	else if (ft_strncmp(line, "F", 1) == 0)
		put_floor_ceiling(line, s_cub);
	else if (ft_strncmp(line, "C", 1) == 0)
		put_floor_ceiling(line, s_cub);
	else if (ft_strncmp(line, "R", 1) == 0)
		put_resolution(line, s_cub);
}

int	parse_map(char *line, t_cub *s_cub)
{
	static int	line_num;

	if (line_num == 0)
		s_cub->map = malloc(sizeof(char *) * 1000);
	s_cub->map[line_num] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	ft_strlcpy(s_cub->map[line_num], line, ft_strlen(line) + 1);
	s_cub->cols = (int)ft_strlen(line) > s_cub->cols ?
		ft_strlen(line) : s_cub->cols;
	line_num++;
	return (line_num);
}

int	is_map(char *line, int *wall_count)
{
	int	idx;
	int	space_onset;	

	space_onset = 1;
	idx = -1;
	while (line[++idx])
	{
		if (!(line [idx] == '1' || line[idx] == ' '))
			return (*wall_count);
		if (line[idx] == '1')
			space_onset = 0;
	}
	
	if (!space_onset)
	{
		(*wall_count)++;
		if (*wall_count == 1)
			return (1);
		else if (*wall_count == 2)
			return (1);
	}
	return (-1);
}
