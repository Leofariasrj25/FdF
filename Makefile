# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 14:03:09 by lfarias-          #+#    #+#              #
#    Updated: 2022/09/24 20:02:53 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC = main.c draw.c map_parser.c
CC = gcc
LIBFT_DIR = ./libft/
## LIBS_LINUX = -g -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

## all:
	## $(CC) $(SRC) $(LIBS_LINUX) -o $(NAME)
	
all:
	make -C $(LIBFT_DIR)
	$(CC) -g -I./mlx_mms/ $(SRC) -Llibft -lft -Lmlx_mms -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
