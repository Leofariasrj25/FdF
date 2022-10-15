# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 14:03:09 by lfarias-          #+#    #+#              #
#    Updated: 2022/10/14 13:41:06 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC = main.c utils.c draw.c map_parser.c transformations.c math_utils.c draw_utils.c
CC = gcc
LIBFT_DIR = ./libft/
LIBS_LINUX = -g -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all:
	make -C $(LIBFT_DIR)
	$(CC) $(SRC) $(LIBS_LINUX) -o $(NAME)
	
## all:
	## make -C $(LIBFT_DIR)
	## $(CC) -g -I./mlx_mms/ $(SRC) -Llibft -lft -Lmlx_mms -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
