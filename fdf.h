/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:05:59 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/13 00:27:15 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"

typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef struct s_map
{
	int				length;
	int				height;
	struct s_coord	***vertices;
}	t_map;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_frame;

typedef struct s_win_data
{
	void	*mlx;
	void	*window;
	t_frame	*frame_buffer;
	t_coord	***wireframe;
}	t_win;

// map
int		map_open(char *map_name);
t_list	*map_read(int map_fd);
t_coord	**map_parse(t_list *map_lines, int *map_length, int *map_height);

//draw
void	mlx_pixel_put_v2(t_frame *frame, int x, int y, int color);
void	draw_line(t_frame *img, t_coord *point0, t_coord *point1, int color);
t_map	*map_get(char *map_name);

// math
int		abs(int n);
double	dg2_rad(double angle);

// transformations
void	isometric(t_coord *point);
#endif
