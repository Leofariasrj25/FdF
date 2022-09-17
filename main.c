/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 14:40:12 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/16 23:21:12 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define W_LENGTH 1280
#define W_HEIGHT 720

typedef struct	s_view_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_win_data	
{
	void	*mlx;
	void	*mlx_win;
	t_data	*frame_buffer;
}	t_win_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	abs(int n)
{
	if (n > 0)
		return (n);
	else
		return (n * -1);
}

//
// slopes between -1 and 0, 0 and 1
void	draw_low_line(t_data *img, int x0, int y0, int x1, int y1, int color)
{
	int	delta_x;
	int	delta_y; int	d_factor; int yi; int	x;
	int y;

	delta_x = x1 - x0;
	delta_y = y1 - y0;
	yi = 1;	
	if (delta_y < 0)
	{
		yi = -1;
		delta_y *= -1;
	}
	d_factor = (2 * delta_y) - delta_x;
	y = y0;
	x = x0;
	while (x < x1)
	{
		my_mlx_pixel_put(img, x, y, color);
		if (d_factor > 0)
		{
			y = y + yi;
			d_factor = d_factor + (2 * (delta_y - delta_x));
		}
		else
			d_factor = d_factor + 2 * delta_y;
		x++;
	}
}

void	draw_high_line(t_data *img, int x0, int y0, int x1, int y1, int color)
{
	int	delta_x;
	int	delta_y;
	int	d_factor;
	int xi;
	int	x;
	int y;

	delta_x = x1 - x0;
	delta_y = y1 - y0;
	xi = 1;	
	if (delta_x < 0)
	{
		xi = -1;
		delta_x *= -1;
	}
	d_factor = (2 * delta_x) - delta_y;
	x = x0;
	y = y0;
	while (y < y1)
	{
		my_mlx_pixel_put(img, x, y, color);
		if (d_factor > 0)
		{
			x = x + xi;
			d_factor = d_factor + (2 * (delta_x - delta_y));
		}
		else
			d_factor = d_factor + 2 * delta_x;
		y++;
	}
}

void	bresenham(t_data *img, int x0, int y0, int x1, int y1, int color)
{
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
			draw_low_line(img, x1, y1, x0, y0, color);
		else
			draw_low_line(img, x0, y0, x1, y1, color);
	}
	else
	{
		if (y0 > y1)
			draw_high_line(img, x1, y1, x0, y0, color);
		else
			draw_high_line(img, x0, y0, x1, y1, color);
	}
}

void draw_lines(t_data *img, int color_palette[5])
{
	static int start;
	int	color;

	if (start >= 5)
		start = 0;
	color = color_palette[start];
	// up, down
	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, W_LENGTH / 2, 0, color);
	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, W_LENGTH / 2, W_HEIGHT, color);
	start++;	
	if (start >= 5)
		start = 0;
	color = color_palette[start];
	// left, right
	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, W_LENGTH, W_HEIGHT / 2, color);
	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, 0, W_HEIGHT / 2, color);
	start++;	
	if (start >= 5)
		start = 0;
	color = color_palette[start];

	// up diagonals
	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, 0, 0, color);
	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, W_LENGTH, 0, color);
	start++;	
	if (start >= 5)
		start = 0;
	color = color_palette[start];	

	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, W_LENGTH / 4, 0, color);
	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, W_LENGTH - (W_LENGTH / 4), 0, color);
	start++;	
	if (start >= 5)
		start = 0;
	color = color_palette[start];	

	// down diagonals
	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, W_LENGTH, W_HEIGHT, color);
	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, 0, W_HEIGHT, color);
	start++;	
	if (start >= 5)
		start = 0;
	color = color_palette[start];	
	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, W_LENGTH / 4, W_HEIGHT, color);
	bresenham(img, W_LENGTH / 2, W_HEIGHT / 2, W_LENGTH - (W_LENGTH / 4), W_HEIGHT, color);
	start++;	
	if (start >= 5)
		start = 0;
	color = color_palette[start];	
}

int	render_next_frame(t_win_data *scene)
{
	int	start;
	int	color_palette[5] = {0xffd319, 0xff901f, 0xff2975, 0xf222ff, 0x8c1eff}; 
	draw_lines(scene->frame_buffer, color_palette); 
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->frame_buffer->img, 0, 0);
	sleep(1);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_win_data	window;
	int	color;

	color = 0x00FF00;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, W_LENGTH, W_HEIGHT, "Hello World!");
	img.img = mlx_new_image(mlx, W_LENGTH, W_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	window.mlx = mlx;
	window.frame_buffer = &img;	
	window.mlx_win = mlx_win;

	mlx_loop_hook(mlx, render_next_frame, &window);
	mlx_loop(mlx);
	return 0;
}

/*int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		color;
	int		square_size;		

	color = 0x00FF00;
	square_size = 100;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, W_HEIGHT, W_LENGTH, "Hello World!");
	img.img = mlx_new_image(mlx, W_HEIGHT, W_LENGTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	// antennas part
	int x_start = (square_size * 3);
	int y_start = 5;

	//row 1
	draw_square(&img, x_start, y_start, square_size, color);
	x_start = (x_start) + (square_size * 6);
	draw_square(&img, x_start, y_start, square_size, color);

	//row 2
	x_start = (square_size * 4);	
	y_start = y_start + square_size;	
	draw_square(&img, x_start, y_start, square_size, color);
	x_start = x_start + (square_size * 4);	
	draw_square(&img, x_start, y_start, square_size, color);

	//body
	int i = 0;
	x_start = (square_size * 3);
	y_start = y_start + square_size;
	while (i < 7)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start = (square_size * 2);
	y_start = y_start + square_size;
	i = 0;
	while (i < 2)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start += square_size;
	i = 0;
	while (i < 3)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start += square_size;
	i = 0;
	while (i < 2)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start = (square_size);
	y_start += square_size;
	i = 0;
	while (i < 11)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start = square_size;
	y_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += square_size * 2;
	i = 0;
	while (i < 7)
	{
		draw_square(&img, x_start, y_start, square_size, color);
		x_start += square_size;
		i++;
	}
	x_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start = square_size;
	y_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start = x_start * 3;	
	draw_square(&img, x_start, y_start, square_size, color);
	x_start *= 3;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += square_size * 2;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += x_start;

	//bottom
	x_start = square_size * 4;	
	y_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += square_size * 2;
	draw_square(&img, x_start, y_start, square_size, color);
	x_start += square_size;
	draw_square(&img, x_start, y_start, square_size, color);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}*/ 
