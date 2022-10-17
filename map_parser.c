/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:15:09 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/16 21:39:12 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

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
		printf("the point color in the map is: %s %d\n", z_and_color[1], atohex(z_and_color[1]));
		printf("the point color in the coord is: %d\n", points[p_i].color);

		free_2d_array((void **) z_and_color);
		p_i++;
		i++;
	}
	line_number++;
	return (points);
}

//TO-DO test code
//TO-DO free resources
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

/*#include <stdio.h>

int main(int argc, char *argv[])
{
	char	*filename = argv[1];	
	t_list	*coords;
	int	fd;

	fd = map_open(filename);
	coords = map_read(fd);
	t_coord	***map_coords = map_parse(coords);

	int i = 0;
	while (map_coords[i])
	{
		printf("\t=== line %d ===\n", i);
		int j = 0;
		while (map_coords[i][j])
		{
			printf("=== node %d ===\n", j);
			printf("x: %d\n", map_coords[i][j]->x);
			printf("y: %d\n", map_coords[i][j]->y);
			printf("z: %d\n", map_coords[i][j]->z);
			printf("=\n");
			j++;
		}
		i++;
	}
}*/
