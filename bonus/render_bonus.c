/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:43:25 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/30 14:38:06 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "../mlx_linux/mlx.h"

int	render_scene(t_app *app_data)
{
	if (app_data->projection == NULL)
		app_data->projection = malloc(sizeof(t_coord) * app_data->map->size);
	if (!app_data->win_close)
	{
		clear_img(app_data, app_data->projection);
		if (!app_data->map_draw)
		{
			copy_points(app_data->projection, app_data->map->points, \
				app_data->map->size);
			render_img(app_data, app_data->projection);
			app_data->map_draw = 1;
		}
		if (app_data->fit)
		{
			fit_img(app_data, app_data->projection);
			app_data->fit = 0;
			app_data->map_draw = 1;
		}
		draw_map(app_data, app_data->projection);
		mlx_put_image_to_window(app_data->mlx, app_data->window, \
			app_data->bitmap->img, 0, 0);
	}
	draw_menu(app_data);
	return (0);
}

void	render_img(t_app *data, t_coord *projection)
{
	z_scale(projection, data->map->z_scale, data->map->size);
	scale(projection, data->map->scale, data->map->size);
	rotate_z(projection, data->map->angles[Z], data->map->size);
	rotate_y(projection, data->map->angles[Y], data->map->size);
	rotate_x(projection, data->map->angles[X], data->map->size);
	translate(projection, &data->map->source, data->map->size);
}

int	on_limits(t_app *data, t_coord *points)
{
	int		i;
	int		canvas_width;
	int		canvas_length;

	i = 0;
	canvas_width = SCREEN_W - CANVAS_MARGIN;
	canvas_length = SCREEN_L - CANVAS_MARGIN;
	while (i < data->map->size)
	{	
		if (points[i].x < (MENU_WIDTH + CANVAS_MARGIN) \
			|| points[i].x >= canvas_width)
			return (0);
		if (points[i].y < CANVAS_MARGIN \
			|| points[i].y >= canvas_length)
			return (0);
		i++;
	}
	return (1);
}

void	fit_img(t_app *data, t_coord *projection)
{
	data->map->scale = 1;
	data->map->source.x = ((SCREEN_W - MENU_WIDTH) / 4) + MENU_WIDTH;
	data->map->source.y = SCREEN_L / 2;
	data->map->source.z = 0;
	copy_points(projection, data->map->points, data->map->size);
	render_img(data, projection);
	while (on_limits(data, projection))
	{
		data->map->scale = data->map->scale + 0.2;
		copy_points(projection, data->map->points, data->map->size);
		isometric(data);
		render_img(data, projection);
	}
}
