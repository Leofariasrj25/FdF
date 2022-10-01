/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:25:35 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/30 22:10:09 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	dg2_rad(double angle)
{
	static const double	pi = 3.14159;

	return (pi * angle / (double) 180.00);
}

int	abs(int n)
{
	if (n > 0)
		return (n);
	else
		return (n * -1);
}
