/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:40:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/21 20:37:29 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_linux/mlx.h"
//#include "mlx_mms/mlx.h"
#include <math.h>
#include <unistd.h>

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
	write_menu(&app_data);
	mlx_loop(app_data.mlx);
	return 0;
}
