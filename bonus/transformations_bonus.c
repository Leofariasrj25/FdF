/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:19:28 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/30 14:41:35 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "math.h"

#define COS 0
#define SIN 1
#define ISO_ANGLE 120
#define ISO_ROT 30 

void	isometric(t_app *app_data)
{
	app_data->map->angles[X] = 60;
	app_data->map->angles[Y] = 1;
	app_data->map->angles[Z] = 310;
	app_data->map->source.x = ((SCREEN_W - MENU_WIDTH) / 4) + MENU_WIDTH;
	app_data->map->source.y = SCREEN_L / 2;
}

void	scale(t_coord *point, double scale, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		point[i].x = point[i].x * scale;
		point[i].y = point[i].y * scale;
		point[i].z = point[i].z * scale;
		i++;
	}
}

void	translate(t_coord *point, t_coord *move, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		point[i].x = point[i].x + move->x;
		point[i].y = point[i].y + move->y;
		point[i].z = point[i].z + move->z;
		i++;
	}
}

void	z_scale(t_coord *projection, double z_scale, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		projection[i].z = (double) projection[i].z * z_scale;
		i++;
	}
}
