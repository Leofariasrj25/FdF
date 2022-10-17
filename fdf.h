/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:05:59 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/16 22:30:34 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"

# define SCREEN_W 1440
# define SCREEN_H 900 

typedef struct s_coord
{
	double			x;
	double			y;
	double			z;
	int				color;
}	t_coord;

typedef struct s_map
{
	int				width;
	int				length;
	int				size;
	double			scale;
	t_coord			source;
	struct s_coord	*points;
}	t_map;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_frame;

typedef struct s_app_info
{
	void	*mlx;
	void	*window;
	t_frame	*bitmap;
	t_map	*map;
	double	map_scale;
	int		screen_w;
	int		screen_l;
}	t_app;

// map
int		map_open(char *map_name);
t_list	*map_read(int map_fd);
t_coord	*map_parse(t_list *map_lines, int *map_length, int *map_height);

//draw
void	mlx_pixel_put_v2(t_frame *frame, int x, int y, int color);
void	draw_line(t_frame *img, t_coord *point0, t_coord *point1, int color);
t_map	*map_get(char *map_name);
void	fit_img(t_app *data, t_coord *projection);

// math
int		abs(int n);
double	dg2_rad(double angle);

// transformations
void	isometric(t_coord *points, int size);
void	scale(t_coord *points, double scale, int size);
void	translate(t_coord *point, t_coord *move, int size);
void	z_scale(t_app *data, t_coord *projection, int size);

//utils
void	free_2d_array(void **matrix);
t_coord	*copy_points(t_coord *dst, t_coord *src, int size);
int	atohex(char *str);
#endif
