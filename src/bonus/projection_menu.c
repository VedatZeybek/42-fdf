/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:02:32 by vzeybek           #+#    #+#             */
/*   Updated: 2025/08/01 13:10:12 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf_bonus.h"

static void	display_1(t_fdf *fdf, int *y,
		int color_white, char *projection_text)
{
	int		color_cyan;

	color_cyan = 0x00FFFF;
	mlx_string_put(fdf->mlx, fdf->win, 20,
		*y, color_white, projection_text);
	*y += 25;
	mlx_string_put(fdf->mlx, fdf->win, 20, *y, color_cyan, "PROJECTION:");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, 30, *y, color_white, "1 - Isometric");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, 30, *y, color_white, "2 - Parallel");
	*y += 30;
	mlx_string_put(fdf->mlx, fdf->win, 20, *y, color_cyan, "ZOOM:");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, 30, *y, color_white, "W - Zoom In");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, 30, *y, color_white, "S - Zoom Out");
	*y += 30;
	mlx_string_put(fdf->mlx, fdf->win, 20, *y, color_cyan, "ROTATION:");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, 30, *y, color_white, "A - Rotate Left");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, 30, *y, color_white, "D - Rotate Right");
	*y += 30;
}

static void	display_2(t_fdf *fdf, int *y, int color_w, int color_cyan)
{
	mlx_string_put(fdf->mlx, fdf->win, 20, *y, color_cyan, "MOVEMENT:");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, 30, *y, color_w, "UP - Move Up");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, 30, *y, color_w, "DOWN - Move Down");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, 30, *y, color_w, "LEFT - Move Left");
	*y += 20;
	mlx_string_put(fdf->mlx, fdf->win, 30, *y, color_w, "RIGHT - Move Right");
	*y += 30;
	mlx_string_put(fdf->mlx, fdf->win, 20, *y, color_cyan, "OTHER:");
	*y += 30;
	mlx_string_put(fdf->mlx, fdf->win, 30, *y, color_w, "ESC - Exit");
}

void	display_projection_menu(t_fdf *fdf)
{
	char	*projection_text;
	int		y_offset;
	int		color_white;
	int		color_yellow;
	int		color_cyan;

	color_white = 0xFFFFFF;
	color_yellow = 0xFFFF00;
	color_cyan = 0x00FFFF;
	y_offset = 20;
	mlx_string_put(fdf->mlx, fdf->win, 20,
		y_offset, color_yellow, "=== FDF CONTROLS ===");
	y_offset += 30;
	if (fdf->projection_type == '1')
		projection_text = "Projection: Isometric";
	else if (fdf->projection_type == '2')
		projection_text = "Projection: Parallel";
	else
		projection_text = "Projection: Unknown";
	display_1(fdf, &y_offset, color_white, projection_text);
	display_2(fdf, &y_offset, color_white, color_cyan);
}
