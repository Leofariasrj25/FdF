/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:40:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/12 13:02:29 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define W_LENGTH 1920 
#define W_HEIGHT 1080 

void	draw_map(t_map *map, t_frame *img, int color)
{
	int	i;
	int	j;
	double	offset_length;
	double	offset_height;
	double	offset_depth;
	t_coord	***wireframe;

	offset_height = 40;
	offset_length = 40;
	offset_depth = 5;
	wireframe = map->vertices;
	i = 0;
	while (wireframe[i])
	{
		j = 0;
		while (wireframe[i][j] && wireframe[i][j + 1])
		{
			t_coord point0;
			t_coord point1;
			//magnify
			point0.x = (wireframe[i][j]->x * offset_length);
			point0.y = (wireframe[i][j]->y * offset_height);
			point0.z = (wireframe[i][j]->z * offset_depth);

			point1.x = (wireframe[i][j + 1]->x * offset_length);
			point1.y = (wireframe[i][j + 1]->y * offset_height);
			point1.z = (wireframe[i][j + 1]->z * offset_depth);
			
			isometric(&point0);
			isometric(&point1);

			point0.x = point0.x + W_LENGTH / (double) 2;
			point0.y = point0.y + W_HEIGHT / (double) 4;

			point1.x = point1.x + W_LENGTH / (double) 2;
			point1.y = point1.y + W_HEIGHT / (double) 4;

			if (point0.z != 0 && point1.z != 0)
				draw_line(img, &point0, &point1, 0xFF1717);
			else
				draw_line(img, &point0, &point1, color);
			j++;

			// draw -y
			if (i != (map->height - 1))
			{
				point1.x = (wireframe[i + 1][j - 1]->x * offset_length);
				point1.y = (wireframe[i + 1][j - 1]->y * offset_height);
				point1.z = (wireframe[i + 1][j - 1]->z * offset_depth);

				isometric(&point1);
				point1.x = point1.x + W_LENGTH / (double) 2;
				point1.y = point1.y + W_HEIGHT / (double) 4;

				if (point0.z != 0 && point1.z != 0)
					draw_line(img, &point0, &point1, 0xFF1717);
				else
					draw_line(img, &point0, &point1, color);
			}
		}
		i++;
	}
	//mlx_pixel_put_v2(img, 700, 700, color);
}

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
	mlx_win.frame_buffer->img = mlx_new_image(mlx_win.mlx, W_LENGTH * 2, W_HEIGHT * 2);
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
