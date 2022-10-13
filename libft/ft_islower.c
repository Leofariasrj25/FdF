/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:38:34 by lfarias-          #+#    #+#             */
/*   Updated: 2022/09/19 17:30:43 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_islower(int c)
{
	char	letter;

	letter = (char) c;
	if (letter >= 97 && letter <= 122)
		return (1);
	return (0);
}