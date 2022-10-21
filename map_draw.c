/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:21:10 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/21 20:40:23 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_app *data)
{
	// first scale, then rotate then translate
	t_coord	*projection;
	int		color;	

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
	create_menu_sidebar(data);
}
