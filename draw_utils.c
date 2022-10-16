/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:43:25 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/16 01:02:49 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	resize_img(t_app *data, t_coord *projection)
{
	
	isometric(projection, data->map->size);
	scale(projection, data->map->scale, data->map->size);
	translate(projection, &data->map->source, data->map->size);
}

int	on_limits(t_app *data, t_coord *points)
{
	int		i;
	int		img_width;
	int		img_height;
	
	i = 0;
	img_width = SCREEN_W - 30;
	img_height = SCREEN_H - 30;
	while (i < data->map->size)
	{	
		if (points[i].x  < 30 || points[i].x  > img_width)
			return (0);
		if (points[i].y < 30 || points[i].y > img_height)
			return (0);
		i++;
	}
	return (1);
}

void	fit_img(t_app *data, t_coord *projection)
{
// enquanto nenhum dos pontos da imagem 'vazar' a tela, continue adicionando a escala.
// multiplique todos os pontos por essa nova escala
// aumente a escala em 0.2
	double	new_scale;
	int		i;

	data->map->scale = 1;
	data->map->source.x = (SCREEN_W / 2); 
	data->map->source.y = (SCREEN_H / 2);
	data->map->source.z = 0;
	resize_img(data, projection);	
	while (on_limits(data, projection))
	{
		data->map->scale = data->map->scale + 0.2;
		copy_points(projection, data->map->points, data->map->size);
		resize_img(data, projection);
	}
}
