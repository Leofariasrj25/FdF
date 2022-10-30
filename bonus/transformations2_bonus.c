/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 00:27:36 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/30 11:36:31 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <math.h>

void	rotate_z(t_coord *points, double angle, int size)
{
	double	cos_theta;
	double	sin_theta;
	double	theta;
	t_coord	holder;
	int		i;

	theta = dg2_rad(angle);
	cos_theta = cos(theta);
	sin_theta = sin(theta);
	i = 0;
	while (i < size)
	{
		holder.x = points[i].x;
		holder.y = points[i].y;
		holder.z = points[i].z;
		points[i].x = (holder.x * cos_theta) - (holder.y * sin_theta); 
		points[i].y = (holder.x * sin_theta) + (holder.y * cos_theta); 
		i++;
	}
}
