/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 08:15:13 by vzeybek           #+#    #+#             */
/*   Updated: 2025/08/01 08:45:29 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf_bonus.h"

void	draw_map(t_fdf *fdf)
{
	int	y;
	int	x;

	y = 0;
	while (y < fdf->row)
	{
		x = 0;
		while (x < fdf->col)
		{
			if (x < fdf->col - 1)
				draw_line(fdf->points[y][x], fdf->points[y][x + 1],
					fdf->mlx, fdf->win);
			if (y < fdf->row - 1)
				draw_line(fdf->points[y][x], fdf->points[y + 1][x],
					fdf->mlx, fdf->win);
			x++;
		}
		y++;
	}
	display_projection_menu(fdf);
}
