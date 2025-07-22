#include "../../inc/fdf_bonus.h"

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
	if ((fdf->col * 20 > 1920) && (fdf->row * 20 > 1200))
	{
		window_width = 1920;
		window_height = 1200;
	}
	else if ((fdf->col * 20 < 800) && (fdf->row * 20 < 600))
	{
		window_width = 800;
		window_height = 600;
	}
	fdf->points = create_points(fdf->map, fdf->col, fdf->row);
	fdf->win = mlx_new_window(fdf->mlx, window_width, window_height, "FDF");
	fdf->offset_x = window_width / 2;
	fdf->offset_y = window_height / 3;
	fdf->scale = 20;
	fdf->projection_type = '1';
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
	mlx_expose_hook(fdf.win, handle_expose, &fdf);
	mlx_loop(fdf.mlx);
}
