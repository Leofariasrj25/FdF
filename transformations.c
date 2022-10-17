/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:19:28 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/17 00:49:20 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"
#include <stdio.h>

void	isometric(t_coord *point, int size)
{
	int		i;
	double	angle;
	double	rot;
	t_coord	holder;

	angle = 330;
	rot = 60; 
	i = 0;
	while (i < size)
	{
		holder.x = point[i].x;
		holder.y = point[i].y;
		holder.z = point[i].z;
		point[i].x = holder.x * cos(dg2_rad(angle));
		point[i].x = point[i].x + holder.y * cos(dg2_rad(angle) + dg2_rad(rot));
		point[i].x = point[i].x + holder.z * cos(dg2_rad(angle) - dg2_rad(rot));
		point[i].y = holder.x * sin(dg2_rad(angle));
		point[i].y = point[i].y + holder.y * sin(dg2_rad(angle) + dg2_rad(rot));
		point[i].y = point[i].y + holder.z * sin(dg2_rad(angle) - dg2_rad(rot));
		i++;
	}
}

void scale(t_coord *point, double scale, int size)
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

void	z_scale(t_app *data, t_coord *projection, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		projection[i].z = projection[i].z / (double) 1.5;
		i++;
	}
}
