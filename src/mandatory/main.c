/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 08:14:51 by vzeybek           #+#    #+#             */
/*   Updated: 2025/08/01 12:52:41 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int	calculate_scale(int win_width, t_fdf *fdf)
{
	int	scale;
	int	scale_coefficient;

	scale_coefficient = 10;
	if (win_width > 600)
		scale_coefficient = 15;
	if (win_width > 1000)
		scale_coefficient = 20;
	if (win_width > 2000)
		scale_coefficient = 40;
	if (win_width > 10000)
		scale_coefficient = 60;
	scale = win_width * scale_coefficient / (fdf->col * fdf->row);
	if (scale < 2)
		scale = 2;
	else if (scale > 50)
		scale = 50;
	return (scale);
}

static void	fill_stats(t_fdf *fdf, char *argv)
{
	int	window_width;
	int	window_height;

	fdf->mlx = mlx_init();
	fdf->row = count_rows(argv);
	fdf->map = read_map(argv, fdf->row);
	fdf->col = count_column(fdf->map);
	window_width = fdf->col * PIXEL_SIZE + MARGIN * 2;
	window_height = fdf->row * PIXEL_SIZE + MARGIN * 2;
	fdf->scale = calculate_scale(window_width, fdf);
	if ((fdf->col * 20 > 1920) || (fdf->row * 20 > 1200))
	{
		window_width = 1920;
		window_height = 1200;
	}
	else if ((fdf->col * 20 < 800) || (fdf->row * 20 < 600))
	{
		window_width = 800;
		window_height = 600;
	}
	fdf->points = create_points(fdf->map, fdf->col, fdf->row);
	fdf->win = mlx_new_window(fdf->mlx, window_width, window_height, "FDF");
	fdf->offset_x = window_width / 2;
	fdf->offset_y = window_height / 3;
}

int	handle_key(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
	{
		free_split(fdf->map);
		free_points(fdf->points, fdf->row);
		free_mlx_simple(fdf);
		free(fdf->mlx);
		exit(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (EXIT_FAILURE);
	fill_stats(&fdf, argv[1]);
	apply_isometric_projection(&fdf);
	draw_map(&fdf);
	mlx_key_hook(fdf.win, handle_key, &fdf);
	mlx_hook(fdf.win, 17, 0, handle_close, &fdf);
	mlx_loop(fdf.mlx);
}
