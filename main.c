/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:40:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/25 19:19:57 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define W_LENGTH 800 
#define W_HEIGHT 600 

void	draw_map(t_map *map, t_frame *img, int color)
{
	int	i;
	int	j;
	int	offset_length;
	int	offset_height;
	t_coord	***wireframe;

	offset_length = W_LENGTH / map->length;
	offset_height = W_HEIGHT / map->height;
	wireframe = map->vertices;
	i = 0;
	while (wireframe[i])
	{
		j = 0;
		while (wireframe[i][j] && wireframe[i][j + 1])
		{
			t_coord point0;
			t_coord point1;
			//draw +x
			point0.x = wireframe[i][j]->x * offset_length;
			point0.y = wireframe[i][j]->y * offset_height;
			point0.z = wireframe[i][j]->z;

			point1.x = wireframe[i][j + 1]->x * offset_length;
			point1.y = wireframe[i][j + 1]->y * offset_height;
			point1.z = wireframe[i][j]->z;

			if (point0.z != 0 && point1.z != 0)
				bresenham(img, &point0, &point1, 0xFF1717);
			else
				bresenham(img, &point0, &point1, color);
			j++;

			// draw -y
			if (i != (map->height - 1))
			{
				point1.x = wireframe[i + 1][j - 1]->x * offset_length;
				point1.y = wireframe[i + 1][j - 1]->y * offset_height;
				point1.z = wireframe[i + 1][j - 1]->z;
				if (point0.z != 0 && point1.z != 0)
					bresenham(img, &point0, &point1, 0xFF1717);
				else
					bresenham(img, &point0, &point1, color);
			}
		}
		i++;
	}
	//mlx_pixel_put_v2(img, 700, 700, color);
}

/*int	render_next_frame(t_win *scene)
{
	int	color;

	color = 0x00FF00;
	draw_map(scene->wireframe, scene->frame_buffer, color);
	mlx_put_image_to_window(scene->mlx, scene->window, scene->frame_buffer->img, 700, 700);
	return (0);
}*/

t_map	*map_get(char *map_name)
{
	int		map_fd;
	t_map	*map;

	map_fd = map_open(map_name);		
	t_list *map_lines = map_read(map_fd);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->vertices = map_parse(map_lines, &map->length, &map->height);
	return (map);
}

int	main(int argc, char *argv[])
{
	t_win	mlx_win;
	t_map	*map;
	//init mlx
	mlx_win.mlx = mlx_init();
	mlx_win.window = mlx_new_window(mlx_win.mlx, W_LENGTH, W_HEIGHT, "Hello World!");
	mlx_win.frame_buffer = malloc(sizeof(t_frame));
	mlx_win.frame_buffer->img = mlx_new_image(mlx_win.mlx, W_LENGTH, W_HEIGHT);
	mlx_win.frame_buffer->addr = mlx_get_data_addr(mlx_win.frame_buffer->img, &mlx_win.frame_buffer->bits_per_pixel,
			&mlx_win.frame_buffer->line_length, &mlx_win.frame_buffer->endian);
	
	// map init
	map = map_get(argv[1]);	
	int	color;

	color = 0x00FF00;
	draw_map(map, mlx_win.frame_buffer, color);
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
