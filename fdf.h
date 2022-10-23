/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:05:59 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/23 13:55:23 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"

# define SCREEN_W 1920
# define SCREEN_L 1080 

# define MENU_WIDTH 200 
# define MENU_BG_COLOR 0x002E323C
# define MENU_KEY_COLOR 0x00AFB0AF
# define MENU_VALUE_COLOR 0x00FF6188

# define CANVAS_MARGIN 30

typedef struct s_coord
{
	double			x;
	double			y;
	double			z;
	int				color;
}	t_coord;

typedef struct s_map
{
	char			*name;
	int				width;
	int				length;
	int				size;
	int				max_depth;
	int				min_depth;
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

// menu
void	write_menu(t_app *data);
void	create_menu_sidebar(t_app *data);

// map
t_map	*map_get(char *map_name);
int		get_line_size(char **fields);
void	get_minmax_z(t_map *map);
int		check_line_format(char **fields);
void	erase_lines(t_list *map_line);

//draw
void	mlx_pixel_put_v2(t_frame *frame, int x, int y, int color);
void	draw_line(t_frame *img, t_coord *point0, t_coord *point1, int color);
void	draw_map(t_app *data);
void	fit_img(t_app *data, t_coord *projection);

// math
int		get_abs(int n);
double	dg2_rad(double angle);

// transformations
void	isometric(t_coord *points, int size);
void	scale(t_coord *points, double scale, int size);
void	translate(t_coord *point, t_coord *move, int size);
void	z_scale(t_app *data, t_coord *projection, int size);

//utils
void	print_str(t_app *data, t_coord *point, int color, char *value);
void	free_2d_array(void **matrix);
t_coord	*copy_points(t_coord *dst, t_coord *src, int size);
int		atohex(char *str);

//error
void	print_err_msg(char *err_msg);
#endif
