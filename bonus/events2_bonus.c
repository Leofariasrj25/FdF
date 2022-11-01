/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:09:30 by lfarias-          #+#    #+#             */
/*   Updated: 2022/10/31 22:14:08 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	close_button(void *param)
{
	t_app	*app_data;

	app_data = (t_app *) param;
	all_you_need_is_kill(app_data);
	exit(0);
}
