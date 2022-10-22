/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:40:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/22 13:35:25 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_linux/mlx.h"
//#include "mlx_mms/mlx.h"
#include <math.h>
#include <unistd.h>

int	load_mlx(t_app *app_data);
int	check_input(int argc, char **argv);

int	main(int argc, char *argv[])
{
	t_app	app_data;

	if (!check_input(argc, argv))
		return (1);
	app_data.map = map_get(argv[1]);
	load_mlx(&app_data);
	draw_map(&app_data);
	mlx_put_image_to_window(app_data.mlx, \
		app_data.window, \
		app_data.bitmap->img, 0, 0);
	write_menu(&app_data);
	mlx_loop(app_data.mlx);
	return (0);
}

int	load_mlx(t_app *app_data)
{
	app_data->mlx = mlx_init();
	app_data->window = mlx_new_window(app_data->mlx, \
		SCREEN_W, \
		SCREEN_L, \
		"FdF - lfarias-");
	app_data->bitmap = malloc(sizeof(t_frame));
	app_data->bitmap->img = mlx_new_image(app_data->mlx, SCREEN_W, SCREEN_L);
	app_data->bitmap->addr = mlx_get_data_addr(app_data->bitmap->img, \
		&app_data->bitmap->bits_per_pixel, \
		&app_data->bitmap->line_length, \
		&app_data->bitmap->endian);
	return (0);
}

int	check_input(int argc, char **argv)
{
	char	*usage = "Usage: ./fdf <filename> [ scale z_size ]";
	if (!((argc - 1) == 1 || (argc - 1) == 3))
	{
		ft_putendl_fd(usage, STDERR_FILENO);
		return (0);	
	}
	return (1);
}
