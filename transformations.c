/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:19:28 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/13 18:27:23 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"

void	isometric(t_coord *point)
{
	double	angle;
	double	rot;
	double	x;
	double	y;
	double	z;

	angle = 30;
	rot = 120;
	x = point->x;
	y = point->y;
	z = point->z;
	point->x = x * cos(dg2_rad(angle));
	point->x = point->x + y * cos(dg2_rad(angle) + dg2_rad(rot));
	point->x = point->x + z * cos(dg2_rad(angle) - dg2_rad(rot));
	point->y = x * sin(dg2_rad(angle));
	point->y = point->y + y * sin(dg2_rad(angle) + dg2_rad(rot));
	point->y = point->y + z * sin(dg2_rad(angle) - dg2_rad(rot));
}

t_coord	*scale(t_coord *point, double scale, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		point[i].x = point[i].x * scale;
		point[i].y = point[i].y * scale;
		point[i].z = point[i].z * scale;
	}
	return (point);
}
