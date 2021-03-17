# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/25 15:39:51 by mkal              #+#    #+#              #
#    Updated: 2021/03/17 23:33:23 by mkal             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBFT = libft
LIBFT_NAME = ft

GNL = gnl

MLX = mlx
MLX_NAME = libmlx.a

FLAGS = -Wall -Wextra -Werror -g
FLAGS_LIB = -L./${MLX} -l${MLX} -L./${LIBFT} -l${LIBFT_NAME}
FLAGS_G = -framework OpenGL -framework AppKit

SRCS = gnl/get_next_line.c \
       gnl/get_next_line_utils.c \
       srcs/main.c \
       srcs/open_cub_file.c \
       srcs/handle_file_error.c \
       srcs/draw_background.c \
       srcs/load_game.c \
       srcs/close_the_window.c \
       srcs/mlx_start.c \
       srcs/game_init.c \
       srcs/ray_calc.c \
       srcs/render_map.c \

OBJS = ${SRCS:.c=.o}

INC = inc

.c.o:
	gcc ${FLAGS} -c $< -o ${<:.c=.o} -I${MLX} -I${GNL} -I${LIBFT} -I${INC}

${NAME} : ${OBJS}
	make all -C ${LIBFT}/
	make all -C ${MLX}/
	gcc ${FLAGS} ${FLAGS_LIB} ${FLAGS_G} ${OBJS} -o ${NAME}

all : ${NAME}

clean : 
	rm -f ${OBJS}
	make clean -C ${LIBFT}
	make clean -C ${MLX}

fclean : clean
	rm -f ${NAME}
	make fclean -C ${LIBFT}

re : fclean all
