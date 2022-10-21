/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:29:11 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/21 13:33:31 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MAX_INT 2147483647
#define MIN_INT -2147483648

void	get_minmax_z(t_map *map);

t_map	*map_get(char *map_name)
{
	int		map_fd;
	t_map	*map;

	map_fd = map_open(map_name);
	t_list *map_lines = map_read(map_fd);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->points = map_parse(map_lines, &map->width, &map->length);
	map->size = map->width * map->length;
	get_minmax_z(map);
	map->name = ft_strrchr(map_name, '/');
	return (map);
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
