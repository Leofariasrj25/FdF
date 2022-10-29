/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 01:08:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/29 01:20:37 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <stdio.h>

int	mouse_press(int button, int x, int y, void *param)
{
	t_app	*app_data;

	app_data = (t_app *) param;
	if (button == 1)
	{
		app_data->mouse_l_press = 1;
		app_data->offset_px = x - app_data->map->source.x;
		app_data->offset_py = y - app_data->map->source.y;
	}
	if (button == 3)
		app_data->mouse_r_press = 1;
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_app	*app_data;

	app_data = (t_app *) param;
	if (app_data->mouse_l_press == 1)
	{
		app_data->map->source.x = x - app_data->offset_px;
		app_data->map->source.y = y - app_data->offset_py;
		app_data->map_draw = 0;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, void *param)
{
	t_app	*app_data;

	x = y;
	y = x;
	app_data = (t_app *) param;
	if (button == 1 && app_data->mouse_l_press == 1)
		app_data->mouse_l_press = 0;
	if (button == 3)
		app_data->mouse_r_press = 0;
	return (0);
}
