/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:29:11 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/22 12:54:49 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MAX_INT 2147483647
#define MIN_INT -2147483648

int	get_line_size(char **fields)
{
	int		size;

	if (!fields)
		return (0);
	size = 0;
	while (fields[size])
	{
		size++;
	}
	return (size);
}

void	get_minmax_z(t_map *map)
{
	int	z_negative;
	int	z_positive;
	int	i;

	if (!map)
		return ;
	z_negative = MAX_INT;
	z_positive = MIN_INT;
	i = -1;
	while (++i < map->size)
	{
		if (map->points[i].z < z_negative)
			z_negative = map->points[i].z;
		else if (map->points[i].z > z_positive)
			z_positive = map->points[i].z;
	}
	map->max_depth = z_positive;
	map->min_depth = z_negative;
}
