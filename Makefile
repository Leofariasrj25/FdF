# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 14:03:09 by lfarias-          #+#    #+#              #
#    Updated: 2022/10/28 15:37:56 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
SRC = 	main.c \
		utils.c \
		app.c \
		app_input.c \
		draw.c \
		draw_utils.c \
		map_draw.c \
		map.c \
		map_utils.c \
		transformations.c \
		math_utils.c \
		render.c \
		render2.c \
		events.c \
		menu.c
SRC_OBJ = $(SRC:.c=.o)
LIBFT_DIR = ./libft/
MLX_DIR = ./mlx_linux/
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	
$(NAME): $(SRC_OBJ)
	make -C $(LIBFT_DIR) libft.a
	make -C $(MLX_DIR) all
	$(CC) $(CFLAGS) $(SRC_OBJ) $(LDFLAGS) -o $(NAME)

all: $(NAME)
	
clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -f *.o

fclean: clean
	rm -f $(LIBFT_DIR)/libft.a
	rm -f $(NAME)

re: clean all
