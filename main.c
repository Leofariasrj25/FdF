/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:40:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/13 20:41:19 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
//#include "mlx_linux/mlx.h"
#include "mlx_mms/mlx.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

// TO-DO reimplement a better drawning algo
void	draw_map(t_map *map, t_frame *img, int color)
{
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
	map->points = map_parse(map_lines, &map->length, &map->height);
	return (map);
}

int	main(int argc, char *argv[])
{
	t_app	app_data;
	t_map	*map;
	
	//init mlx
	app_data.mlx = mlx_init();
	printf("Screen resolution: %dx%d\n", app_data.screen_w, app_data.screen_l);
	app_data.window = mlx_new_window(app_data.mlx, app_data.screen_w, app_data.screen_l, "FdF - lfarias-");
	app_data.frame_buffer = malloc(sizeof(t_frame));
	app_data.frame_buffer->img = mlx_new_image(app_data.mlx, app_data.screen_w, app_data.screen_l);
	app_data.frame_buffer->addr = mlx_get_data_addr(app_data.frame_buffer->img, &app_data.frame_buffer->bits_per_pixel,
			&app_data.frame_buffer->line_length, &app_data.frame_buffer->endian);
	
	// map init
	map = map_get(argv[1]);	
	int	color;

	color = 0x00FF00;
	draw_map(map, app_data.frame_buffer, color);
	mlx_put_image_to_window(app_data.mlx, app_data.window, app_data.frame_buffer->img, 0, 0);
	mlx_loop(app_data.mlx);
	return 0;
}
