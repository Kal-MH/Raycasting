/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:06:32 by mkal              #+#    #+#             */
/*   Updated: 2021/03/17 23:51:45 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <math.h>
# include <limits.h>
# include <float.h>

# include <stdio.h>
# include <time.h>
# include <mach/mach.h>
# include <mach/mach_time.h>

# define _USE_MATH_DEFINES
# define VALID_MAP_CHARACTERS " 01234NSEW"

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_DESTROY 17

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_FOWARD 126
# define KEY_BACKWARD 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define M_SPD 0.04 

# define FPS 30
# define FRAME_TIME_LENGTH (1000 / FPS)
# define PI 3.14159265
# define TWO_PI 6.28318530
# define FOV_ANGLE (60 * (PI / 180))
# define TILE_SIZE 10

# pragma pack(push, 1)

/*
** ray[0~1] : 광선의 단위벡터
** ray[2~3] : 광선의 현재위치
** ray[4~5] : 광선이 부딪힌 위치
** ray[6]   : 광선이 진행중이면 0
** 			  1이면 북쪽벽, 2는 남, 3은 서, 4는 동
** ray[7]   : 광선이 부딪힌 곳까지의 거리
** ray[8]   : 광선이 벽의 어느부분에 부딪혔는가(0~1)
** ray[9]	: 광선이 스프라이트에 부딪혔는가?
** ray[10]	: 스프라이트까지의 거리
** ray[11]	: 스프라이트의 어느부분에 부딪혔는가(0~1)
*/

typedef	struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			*width;
	int			*height;
}				t_img;

typedef struct	s_player
{
	double	x;
	double	y;
	double	rotation_angle;
	double	walk_speed;
	double	turn_speed;	
	int	turn_direction;
	int	walk_direction;
}		t_player;

typedef struct	s_ray
{
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int	was_hit_vertical;
	int	is_ray_facing_up;
	int	is_ray_facing_down;
	int	is_ray_facing_left;
	int	is_ray_facing_right;
	int	wall_hit_content;
}		t_ray;

typedef struct	s_cub
{
	double	f[3];
	double	c[3];
	int	r[2];
	int	cols;
	int	lines;
	int	num_of_rays;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*sprite;
	char	**map;
	void	*mlx;
	void	*win;
	t_player	*player;
	t_ray		*rays;
	t_img	*n;
	t_img	*s;
	t_img	*w;
	t_img	*e;
	t_img	*sp;
	t_img	*screen;
}		t_cub;

# pragma pack(pop)

int	is_map(char *line, int	*is_map_ok);
int	parse_map(char *line, t_cub *s_cub);
void	devide_spec_content(char *line, t_cub *s_cub);

int	ft_in_set(char c, char const *set);
int	handle_map_check_valid(t_cub *s_cub);
int	handle_map_left_right_borders(t_cub *s_cub);
int	handle_file_check_nswesrfc(t_cub *s_cub);
int	handle_is_map_file_error(t_cub *s_cub);

void			load_game(t_cub *s_cub);
void			draw_background(t_cub *s_cub);
int	close_the_window(t_cub *s_cub);
void	mlx_start(t_cub *s_cub);
void	game_init(t_cub *s_cub);
void	cast_all_rays(t_cub *s_cub);
int	map_has_wall_at(t_cub *s_cub, double x, double y);
void	render_map(t_cub *s_cub);
#endif
