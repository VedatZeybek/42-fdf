/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 08:15:32 by vzeybek           #+#    #+#             */
/*   Updated: 2025/08/01 08:15:33 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf_bonus.h"

static void	rotate_point_screen(t_point *p, int pivot_x, int pivot_y, float rad)
{
	int		x;
	int		y;
	int		rotated_x;
	int		rotated_y;

	x = p->screen_x - pivot_x;
	y = p->screen_y - pivot_y;
	rotated_x = (int)(x * cos(rad) - y * sin(rad));
	rotated_y = (int)(x * sin(rad) + y * cos(rad));
	p->screen_x = rotated_x + pivot_x;
	p->screen_y = rotated_y + pivot_y;
}

void	rotate_screen_coordinates(t_fdf *fdf)
{
	int		i;
	int		j;
	float	rad;

	rad = fdf->rotation_angle * 3.14 / 180.0f;
	i = 0;
	while (i < fdf->row)
	{
		j = 0;
		while (j < fdf->col)
		{
			rotate_point_screen(&fdf->points[i][j],
				fdf->offset_x, fdf->offset_y, rad);
			j++;
		}
		i++;
	}
}
