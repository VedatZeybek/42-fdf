/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 08:14:35 by vzeybek           #+#    #+#             */
/*   Updated: 2025/08/01 11:38:01 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int	get_color(int z)
{
	if (z <= 0)
		return (0x1E90FF);
	else if (z > 0 && z <= 5)
		return (0x00FF00);
	else if (z > 5 && z <= 15)
		return (0xFFFF00);
	else if (z > 15 && z <= 30)
		return (0xFF0000);
	else
		return (0xFF0000);
}

t_rgb	extract_rgb(int color)
{
	t_rgb	rgb;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (rgb);
}

int	interpolate_channel(int start, int end, float t)
{
	return (start + (end - start) * t);
}

int	get_gradient_color(int color_start, int color_end, float t)
{
	t_rgb	start;
	t_rgb	end;
	t_rgb	result;

	start = extract_rgb(color_start);
	end = extract_rgb(color_end);
	result.r = interpolate_channel(start.r, end.r, t);
	result.g = interpolate_channel(start.g, end.g, t);
	result.b = interpolate_channel(start.b, end.b, t);
	return ((result.r << 16) | (result.g << 8) | result.b);
}
