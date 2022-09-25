/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:40:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/25 17:18:03 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define W_LENGTH 1000
#define W_HEIGHT 1000

void	draw_map(t_coord ***wireframe, t_frame *img, int color)
{
	int		i;
	int		j;
	int		v;

	i = 0;
	while (wireframe[i])
	{
		j = 1;
		while (wireframe[i][j - 1] && wireframe[i][j])
		{
			printf("x0: %d y0: %d\n", wireframe[i][j - 1]->x, wireframe[i][j - 1]->y);
			printf("x1: %d y1: %d\n", wireframe[i][j]->x, wireframe[i][j]->y);
			printf("---\n");
			bresenham(img, wireframe[i][j - 1], wireframe[i][j], color);
			j++;
		}
		i++;
	}
	//mlx_pixel_put_v2(img, 700, 700, color);
}

int	render_next_frame(t_win *scene)
{
	int	color;

	color = 0x00FF00;
	draw_map(scene->wireframe, scene->frame_buffer, color);
	mlx_put_image_to_window(scene->mlx, scene->window, scene->frame_buffer->img, 700, 700);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_win	mlx_win;
	t_coord	***map;

	//init mlx
	mlx_win.mlx = mlx_init();
	mlx_win.window = mlx_new_window(mlx_win.mlx, W_LENGTH, W_HEIGHT, "Hello World!");
	mlx_win.frame_buffer = malloc(sizeof(t_frame));
	mlx_win.frame_buffer->img = mlx_new_image(mlx_win.mlx, W_LENGTH, W_HEIGHT);
	mlx_win.frame_buffer->addr = mlx_get_data_addr(mlx_win.frame_buffer->img, &mlx_win.frame_buffer->bits_per_pixel,
			&mlx_win.frame_buffer->line_length, &mlx_win.frame_buffer->endian);
	
	// map init
	int map_fd = map_open(argv[1]);		
	t_list *map_lines = map_read(map_fd);
	map = map_parse(map_lines);
	mlx_win.wireframe = map;
	
	int	color;

	color = 0x00FF00;
	draw_map(mlx_win.wireframe, mlx_win.frame_buffer, color);
	mlx_put_image_to_window(mlx_win.mlx, mlx_win.window, mlx_win.frame_buffer->img, 0, 0);
	mlx_loop(mlx_win.mlx);
	return 0;
}

/*int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		color;
	int		square_size;		

	color = 0x00FF00;
	square_size = 100;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, W_HEIGHT, W_LENGTH, "Hello World!");
	img.img = mlx_new_image(mlx, W_HEIGHT, W_LENGTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	// antennas part
	int x_start = (square_size * 3);
	int y_start = 5;

	//row 1
	draw_square(&img, x_start, y_start, square_size, color);
	x_start = (x_start) + (square_size * 6);
	draw_square(&img, x_start, y_start, square_size, color);

	//row 2
	x_start = (square_size * 4);	
	y_start = y_start + square_size;	
	draw_square(&img, x_start, y_start, square_size, color);
	x_start = x_start + (square_size * 4);	
	draw_square(&img, x_start, y_start, square_size, color);

	//bodye
	int i = 0;
	x_start = (square_size * 3);
	y_start = y_start + square_size;
	while (i < 7)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start = (square_size * 2);
	y_start = y_start + square_size;
	i = 0;
	while (i < 2)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start += square_size;
	i = 0;
	while (i < 3)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start += square_size;
	i = 0;
	while (i < 2)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start = (square_size);
	y_start += square_size;
	i = 0;
	while (i < 11)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start = square_size;
	y_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += square_size * 2;
	i = 0;
	while (i < 7)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start = square_size;
	y_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start = x_start * 3;	
	draw_square(&img, x_start, y_start, square_size, color);
	x_start *= 3;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += square_size * 2;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += x_start;

	//bottom
	x_start = square_size * 4;	
	y_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += square_size * 2;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}*/ 
