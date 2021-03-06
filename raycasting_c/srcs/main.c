/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:55:41 by mkal              #+#    #+#             */
/*   Updated: 2021/03/05 10:40:11 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	valid_cub_file_name(char *file_name)
{
	char	*dot_pointer;

	dot_pointer = ft_strchr(file_name, '.');
	if (dot_pointer && ft_strncmp(dot_pointer, ".cub", 4) == 0)
		return (1);
	return (0);
}

void	check_files_valid(char **file_name)
{
	int	fd;

	if ((fd = open(*file_name, O_RDONLY)) <= 0)
		*file_name = NULL;
	else
		close(fd);
}

void	open_cub_file(t_cub *s_cub, char *map_name)
{
	int	fd;
	char	*line;
	int	wall_count;
	int	is_map_value;

	wall_count = 0;
	fd = open(map_name, O_RDONLY);
	s_cub->cols = 0;
	s_cub->f[0] = -1;
	s_cub->f[1] = -1;
	s_cub->f[2] = -1;
	s_cub->c[0] = -1;
	s_cub->c[1] = -1;
	s_cub->c[2] = -1;
	while (get_next_line(fd, &line))
	{
		is_map_value = is_map(line, &wall_count);
		if (is_map_value > 0)
			s_cub->lines = parse_map(line, s_cub);
		else if (is_map_value == 0)
			devide_spec_content(line, s_cub);
	}
	close(fd);
	check_files_valid(&s_cub->no);
	check_files_valid(&s_cub->so);
	check_files_valid(&s_cub->ea);
	check_files_valid(&s_cub->we);
	check_files_valid(&s_cub->sprite);
	s_cub->r[0] = (wall_count < 2) ? 0 : s_cub->r[0];
	printf("%d(wall_count)\n",wall_count);
}

int	main(int argc, char *argv[])
{
	t_cub	s_cub;

	if (argc > 1 && valid_cub_file_name(argv[1]))
		open_cub_file(&s_cub, argv[1]);
	if (argc > 1 && !handle_is_map_file_error(&s_cub))
	{
		s_cub.mlx = mlx_init();
		game_init(&s_cub);
		ray_calc(&s_cub);
		s_cub.win = mlx_new_window(s_cub.mlx, s_cub.r[0], s_cub.r[1], "cub3d");
		load_images(&s_cub);
		draw_background(&s_cub);
		draw_walls(&s_cub);
		draw_sprite(&s_cub);
		mlx_put_image_to_window(s_cub.mlx, s_cub.win,
			s_cub.screen->img_ptr, 0, 0);
		if (argc == 3 && !ft_strncmp(argv[2], "--save", 6))
			save_bmp(&s_cub);
		mlx_start(&s_cub);
	}
	write(1, "Error\n", 6);
	return (0);
}
