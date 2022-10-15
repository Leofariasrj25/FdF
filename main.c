/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:40:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/14 23:34:08 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_linux/mlx.h"
//#include "mlx_mms/mlx.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

// TO-DO reimplement a better drawning algo
void	draw_map(t_app *data, int color)
{
	// first scale, then rotate then translate
	t_coord	*projection;
	
	projection = malloc(sizeof(t_coord) * data->map->size);
	copy_points(projection, data->map->points, data->map->size);
	fit_img(data, projection);
	int i = 0;
	while (i < data->map->size)
	{
		printf("points %d x = %lf and y = %lf\n", i, projection[i].x, projection[i].y);
		if (projection[i].x < 0 || projection[i].x > SCREEN_W)
		{
			i++;
			continue;
		}
		if (projection[i].y < 0 || projection[i].y > SCREEN_H)
		{
			i++;
			continue;
		}
		mlx_pixel_put_v2(data->bitmap, projection[i].x, projection[i].y, color);
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
