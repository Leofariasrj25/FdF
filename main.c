/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:40:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/21 14:13:03 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_linux/mlx.h"
//#include "mlx_mms/mlx.h"
#include <math.h>
#include <unistd.h>

void	draw_map(t_app *data, int color)
{
	// first scale, then rotate then translate
	t_coord	*projection;
	
	projection = malloc(sizeof(t_coord) * data->map->size);
	copy_points(projection, data->map->points, data->map->size);
	fit_img(data, projection);
	int i = 0;
	int j = 1;
	// hypothesis, start to draw from the end of the row towards the beginning
	while (i < (data->map->size - data->map->width - 1))
	{
		if (i < (data->map->width * j - 1))	
		{
			if (projection[i].color == 0 && projection[i + 1].color == 0)
				color =	0x00FFFFFF;
			else
				color = projection[i].color;
			draw_line(data->bitmap, &projection[i], &projection[i + 1], color);	
			if (projection[i].color == 0 && projection[i + data->map->width].color == 0)
				color =	0x00FFFFFF;
			else
				color = projection[i].color;
			draw_line(data->bitmap, &projection[i], &projection[i + data->map->width], color);	
		}
		else
			j++;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_app	app_data;
	
	//init mlx
	app_data.mlx = mlx_init();
	app_data.window = mlx_new_window(app_data.mlx, SCREEN_W, SCREEN_L, "FdF - lfarias-");
	app_data.bitmap = malloc(sizeof(t_frame));
	app_data.bitmap->img = mlx_new_image(app_data.mlx, SCREEN_W, SCREEN_L);
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
