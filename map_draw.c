/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:21:10 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/23 17:03:07 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color_pick(t_coord *p0, t_coord *p1);

void	draw_map(t_app *data)
{
	// first scale, then rotate then translate
	t_coord	*projection;
	int		i;
	int		j;
	int		color;	

	projection = malloc(sizeof(t_coord) * data->map->size);
	copy_points(projection, data->map->points, data->map->size);
	fit_img(data, projection);
	i = 0;
	j = 1;
	while (i < (data->map->size - data->map->width - 1))
	{
		if (i < (data->map->width * j - 1))	
		{
			color = color_pick(&projection[i], &projection[i + 1]);
			draw_line(data->bitmap, &projection[i], &projection[i + 1], color);	
			color = color_pick(&projection[i], &projection[i + data->map->width]);
			draw_line(data->bitmap, &projection[i], &projection[i + data->map->width], color);	
		}
		else
			j++;
		i++;
	}
	create_menu_sidebar(data);
	free(projection);
}

int	color_pick(t_coord *p0, t_coord *p1)
{
	int	color;

	color = 0;
	if ((p0->color == 0 && p1->color == 0) && (p0->z != 0 && p1->z != 0))
		color = 0xf08d2e;
	else if (p0->color == 0 && p1->color == 0)
		color = 0x20C20E;
	else if (p0->color != 0)
		color = p0->color;
	return (color);
}


