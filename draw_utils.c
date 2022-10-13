/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:43:25 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/13 20:22:53 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_limits(t_app *data, t_coord *projection, double scale)
{
	int		i;
	int		img_length;
	int		img_width;
	t_coord	*points;
	
	i = 0;
	points = data->map->points;
	img_length = data->screen_l;
	img_width = data->screen_w;
	while (i < data->map->size)
	{
		if (points[i].x * scale < img_length || points[i].x * scale > img_length)
			return (0);
		if (points[i].y * scale < img_width || points[i].y * scale > img_width)
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

	new_scale = data->map->scale;
	while (on_limits(data, projection, new_scale + 0.2))
	{
		new_scale += 0.2;
	}
	data->map->scale = new_scale;
	scale(projection, data->map->scale, data->map->size);
}
