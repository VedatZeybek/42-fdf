#include "fdf.h"

void	fill_stats(t_fdf *fdf, char *argv)
{	
	fdf->mlx = mlx_init();
	fdf->row = count_rows(argv);
	fdf->map = read_map(argv, fdf->row);
	fdf->col = count_column(fdf->map);
	fdf->points = create_points(fdf->map, fdf->col, fdf->row);
}


int main(int argc, char **argv)
{

	t_fdf fdf;
	

	fill_stats(&fdf, argv[1]);
	
	int window_width = fdf.col * PIXEL_SIZE + MARGIN * 2;
    int window_height = fdf.row * PIXEL_SIZE + MARGIN * 2;
    
    window_width = fdf.col * 20;
    window_height = fdf.row * 20;

	if ((fdf.col * 20 > 1600) && (fdf.row * 20 > 1200))
    {
		window_width = 1600;
		window_height = 1200;
	}
	else if ((fdf.col * 20 < 800) && (fdf.row * 20 < 600))
	{
		window_width = 800;
		window_height = 600;
	}

	fdf.win = mlx_new_window(fdf.mlx, window_width, window_height, "FDF");

	fdf.offset_x = window_width / 2;
    fdf.offset_y = window_height / 3;
	fdf.scale = 20;
	
	apply_isometric_projection(&fdf);

	draw_map(&fdf);

	mlx_key_hook(fdf.win, handle_key, &fdf);
	mlx_hook(fdf.win, 17, 0, handle_close, &fdf);

	mlx_expose_hook(fdf.win, handle_expose, &fdf);


	mlx_loop(fdf.mlx);
}

