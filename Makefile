# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 14:03:09 by lfarias-          #+#    #+#              #
#    Updated: 2022/10/28 14:16:23 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC = main.c utils.c app.c app_input.c draw.c draw_utils.c map_draw.c map.c \
	  map_utils.c transformations.c math_utils.c render.c render2.c events.c menu.c
BONUS_SRC = main_bonus.c
BONUS_DIR = ./bonus/
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft/
LIBS_LINUX = -O3 -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	
all:
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(SRC) $(LIBS_LINUX) -o $(NAME)
	
##all:
	##make -C $(LIBFT_DIR)
	##$(CC) -g -I./mlx_mms/ $(SRC) -Llibft -lft -Lmlx_mms -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
