/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:43:25 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/23 17:02:40 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_linux/mlx.h"
#include "menu.h"

void	resize_img(t_app *data, t_coord *projection)
{
	z_scale(data, projection, data->map->size);
	isometric(projection, data->map->size);
	scale(projection, data->map->scale, data->map->size);
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
		if (points[i].x  < (MENU_WIDTH + CANVAS_MARGIN) || points[i].x  >= canvas_width)
			return (0);
		if (points[i].y < CANVAS_MARGIN || points[i].y >= canvas_length)
			return (0);
		i++;
	}
	return (1);
}

void	fit_img(t_app *data, t_coord *projection)
{
	double	new_scale;
	int		i;

	data->map->scale = 1;
	data->map->source.x = ((SCREEN_W - MENU_WIDTH) / 4) + MENU_WIDTH;
	data->map->source.y = SCREEN_L / 2;
	data->map->source.z = 0;
	resize_img(data, projection);	
	while (on_limits(data, projection))
	{
		data->map->scale = data->map->scale + 0.2;
		copy_points(projection, data->map->points, data->map->size);
		resize_img(data, projection);
	}
}

void	create_menu_sidebar(t_app *data)
{
	int	i;
	t_coord	p0;
	t_coord	p1;

	i = 0;
	while (i < SCREEN_L)
	{
		p0.x = 0;
		p0.y = i;
		p0.z = 0;
		p1.x = MENU_WIDTH;
		p1.y = i;
		p1.z = 0;
		draw_line(data->bitmap, &p0, &p1, MENU_BG_COLOR);
		i++;
	}
}
