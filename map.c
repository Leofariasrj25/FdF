/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:15:09 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/22 13:08:20 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <fcntl.h>

// Manages all of the map reading and conversion logic
t_map	*map_get(char *map_name)
{
	int		map_fd;
	t_map	*map;

	map_fd = map_open(map_name);
	//if (map_fd == -1)
		//all_you_need_is_kill(map_name);
	t_list *map_lines = map_read(map_fd);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->points = map_parse(map_lines, &map->width, &map->length);
	map->size = map->width * map->length;
	get_minmax_z(map);
	map->name = ft_strrchr(map_name, '/');
	if (!map->name)
		map->name = map_name;
	return (map);
}

int	map_open(char *map_name)
{
	int	fd;

	if (!map_name)
		return (-1);
	fd = open(map_name, O_RDONLY);
	return (fd);
}

t_list	*map_read(int map_fd)
{
	t_list	*map_lines;
	t_list	*node;
	char	*line;

	map_lines = NULL;
	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			break ;
		node = ft_lstnew(line);
		if (map_lines == NULL)
			map_lines = node;
		else
			ft_lstadd_back(&map_lines, node);
	}
	return (map_lines);
}

// Test code
t_coord	*map_extract_coords(char **fields, t_coord *points)
{	
	static int	line_number;
	static int	p_i;
	int			i;
	char		**z_and_color;

	i = 0;
	while (fields[i])
	{
		z_and_color = ft_split(fields[i], ',');
		points[p_i].x = i;
		points[p_i].y = line_number;
		points[p_i].z = ft_atoi(z_and_color[0]);
		points[p_i].color = atohex(z_and_color[1]);	
		free_2d_array((void **) z_and_color);
		p_i++;
		i++;
	}
	line_number++;
	return (points);
}

t_coord	*map_parse(t_list *map_lines, int *map_length, int *map_height)
{
	t_list	*line;
	char	**fields;
	t_coord	*points;

	line = map_lines;
	points = NULL;
	while (line)
	{
		fields = ft_split((char *) line->content, ' ');
		if (points == NULL)
		{
			*map_length = get_line_size(fields);
			*map_height = ft_lstsize(map_lines);
			points = malloc(sizeof(t_coord) * (*map_length * *map_height));
		}
		map_extract_coords(fields, points);
		free_2d_array((void **) fields);
		line = line->next;
	}
	return (points);
}
