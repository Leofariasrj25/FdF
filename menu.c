/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:49:31 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/21 20:10:46 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MENU_LINE_HEIGHT 20
#define MENU_LINE_MARGIN 20

void	write_map_info(t_app *data);
void	write_controls(t_app *data);

void	write_menu(t_app *data)
{
	write_map_info(data);
	write_controls(data);
}

void	draw_key_value(t_app *data, t_coord *point, char *key, char *value)
{
	print_str(data, point, MENU_KEY_COLOR, key);
	point->x = 100;
	print_str(data, point, MENU_VALUE_COLOR, value); 
	point->y = point->y + MENU_LINE_HEIGHT;
	point->x = MENU_LINE_HEIGHT;
}

void	write_controls(t_app *data)
{
	t_coord	point;

	point.x = MENU_LINE_MARGIN;
	point.y = 300;
	print_str(data, &point, MENU_KEY_COLOR, " ==== CONTROLS ==== ");
	point.y = point.y + MENU_LINE_HEIGHT;
	print_str(data, &point, MENU_KEY_COLOR, "ESC : CLOSE");
	point.y = point.y + MENU_LINE_HEIGHT;
	print_str(data, &point, MENU_KEY_COLOR, "P : PARALLEL VIEW");
	point.y = point.y + MENU_LINE_HEIGHT;
	print_str(data, &point, MENU_KEY_COLOR, "I : ISOMETRIC VIEW");
}

void	write_map_info(t_app *data)
{
	t_coord	point;
	char	*value;

	point.x = 20;
	point.y = 100;
	print_str(data, &point, MENU_KEY_COLOR, " ==== MAP INFO ==== ");
	point.y = point.y + MENU_LINE_HEIGHT;
	draw_key_value(data, &point, "NAME :", data->map->name);
	value = ft_itoa(data->map->size);	
	draw_key_value(data, &point, "SIZE :", value);
	free(value);
	value = ft_itoa(data->map->width);
	draw_key_value(data, &point, "LENGTH (X) :", value);
	free(value);
	value = ft_itoa(data->map->length);
	draw_key_value(data, &point, "HEIGHT (Y):", value);
	free(value);
	value = ft_itoa(data->map->max_depth);
	draw_key_value(data, &point, "+WIDTH (Z) :", value);
	free(value);
	value = ft_itoa(data->map->min_depth);
	draw_key_value(data, &point, "-WIDTH (Z) :", value);
	free(value);
}

