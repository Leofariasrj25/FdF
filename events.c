/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 20:35:11 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/25 19:20:02 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx_linux/mlx.h"

int	key_press(int keycode, void *param)
{
	t_app	*app_data;

	app_data = (t_app *) param;
	if (keycode == F_KEY)
		app_data->fit = 1;
	if (keycode == ESC_KEY)
	{
		all_you_need_is_kill(app_data);
		exit(0);
	}
	return (0);
}

int	close_button(void *param)
{
	t_app	*app_data;

	app_data = (t_app *) param;
	all_you_need_is_kill(app_data);
	exit(0);
}
