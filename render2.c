/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:43:58 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/26 18:49:55 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_last_col(t_app *data, t_coord *projection);
void	clear_last_line(t_app *data, t_coord *projection);

void	clear_img(t_app *data, t_coord *projection)
{
	int		i;
	int		j;
	int		color;	

	i = 0;
	j = 1;
	color = 0x000000;
	while (i < (data->map->size - data->map->width - 1))
	{
		if (i < (data->map->width * j - 1))
		{
			draw_line(data->bitmap, &projection[i], &projection[i + 1], color);
			draw_line(data->bitmap, &projection[i], \
				&projection[i + data->map->width], color);
		}
		else
			j++;
		i++;
	}
	clear_last_line(data, projection);
	clear_last_col(data, projection);
}

void	clear_last_line(t_app *data, t_coord *projection)
{
	int	i;
	int	color;

	color = 0x00000000;
	i = (data->map->size - data->map->width);
	while (i < (data->map->size - 1))
	{
		draw_line(data->bitmap, &projection[i], &projection[i + 1], color);
		i++;
	}
}
void clear_last_col(t_app *data, t_coord *projection)
{
	int	i;
	int	color;

	color = 0x000000;
	i = data->map->width - 1;
	while (i < data->map->size - 1)
	{
		draw_line(data->bitmap, &projection[i], \
			&projection[i + data->map->width], color);
		i += data->map->width;
	}
}
