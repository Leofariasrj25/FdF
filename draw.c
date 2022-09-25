/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:20:22 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/25 17:31:26 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_frame *data, int x, int y, int color)
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
void	draw_low_line(t_frame *img, t_coord *point0, t_coord *point1, int color)
{
	int	delta_x;
	int	delta_y; int	d_factor; int yi; int	x;
	int y;

	delta_x = point1->x - point0->x;
	delta_y = point1->y - point0->y;
	yi = 1;	
	if (delta_y < 0)
	{
		yi = -1;
		delta_y *= -1;
	}
	d_factor = (2 * delta_y) - delta_x;
	y = point0->y;
	x = point0->x;
	while (x < point1->x)
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

void	draw_high_line(t_frame *img, t_coord *point0, t_coord *point1, int color)
{
	int	delta_x;
	int	delta_y;
	int	d_factor;
	int xi;
	int	x;
	int y;

	delta_x = point1->x - point0->x;
	delta_y = point1->y - point0->y;
	xi = 1;	
	if (delta_x < 0)
	{
		xi = -1;
		delta_x *= -1;
	}
	d_factor = (2 * delta_x) - delta_y;
	x = point0->x;
	y = point0->y;
	while (y < point1->y)
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

void	bresenham(t_frame *img, t_coord *point0, t_coord *point1, int color)
{
	if (abs(point1->y - point0->y) < abs(point1->x - point0->x))
	{
		if (point0->x > point1->x)
			draw_low_line(img, point1, point0, color);
		else
			draw_low_line(img, point0, point1, color);
	}
	else
	{
		if (point0->y > point1->y)
			draw_high_line(img, point1, point0, color);
		else
			draw_high_line(img, point0, point1, color);
	}
}

