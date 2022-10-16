/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:40:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/16 00:55:14 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_linux/mlx.h"
//#include "mlx_mms/mlx.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

/* TO-DO reimplement a better drawning algo
void	draw_segment(t_app *data, t_coord *point0, t_coord *point1, int color)
{
		// iterate over all the points
		// if the point is valid, meaning, it's inside the screen then do this:
		// get the first point, connect it to other two points
		// those points will be point[i] point[i + 1][j + 1] point[i] point[i + 1] point[i + 1][j + 1]
		// always draw the points in clockwise direction
		draw_line(data->bitmap, point0, point1, color);
}*/

void	draw_map(t_app *data, int color)
{
	// first scale, then rotate then translate
	t_coord	*projection;
	
	projection = malloc(sizeof(t_coord) * data->map->size);
	copy_points(projection, data->map->points, data->map->size);
	fit_img(data, projection);
	int i = 0;
	int j = 1;
	while (i < (data->map->size - data->map->width - 1))
	{
		if (i < (data->map->width * j - 1))	
		{
			if (projection[i].z != 0 || projection[i + 1].z != 0)
				color = 0xFF0000;
			else
				color = 0x00FF00;
			draw_line(data->bitmap, &projection[i], &projection[i + 1], color);	
			if (projection[i].z != 0 || projection[i + data->map->width].z != 0)
				color = 0xFF0000;
			else
				color = 0x00FF00;
			draw_line(data->bitmap, &projection[i], &projection[i + data->map->width], color);	
		}
		else
			j++;
		i++;
	}
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
	map->points = map_parse(map_lines, &map->width, &map->length);
	map->size = map->width * map->length;
	map->scale = 1;
	return (map);
}

int	main(int argc, char *argv[])
{
	t_app	app_data;
	
	//init mlx
	app_data.mlx = mlx_init();
	app_data.window = mlx_new_window(app_data.mlx, SCREEN_W, SCREEN_H, "FdF - lfarias-");
	app_data.bitmap = malloc(sizeof(t_frame));
	app_data.bitmap->img = mlx_new_image(app_data.mlx, SCREEN_W, SCREEN_H);
	app_data.bitmap->addr = mlx_get_data_addr(app_data.bitmap->img, &app_data.bitmap->bits_per_pixel,
			&app_data.bitmap->line_length, &app_data.bitmap->endian);
	
	// map init
	app_data.map = map_get(argv[1]);	
	int	color;

	color = 0x00FF00;
	draw_map(&app_data, color);
	mlx_put_image_to_window(app_data.mlx, app_data.window, app_data.bitmap->img, 0, 0);
	mlx_loop(app_data.mlx);
	return 0;
}
