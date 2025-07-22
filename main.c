#include "fdf.h"

int main(int argc, char **argv)
{

	t_vars fdf;
	
	fdf.mlx = mlx_init();
	fdf.row = count_rows(argv[1]);
	fdf.map = read_map(argv[1], fdf.row);
	fdf.col = count_column(fdf.map);
	
	fdf.points = create_points(fdf.map, fdf.col, fdf.row);
	
	int window_width = fdf.col * PIXEL_SIZE + MARGIN * 2;
    int window_height = fdf.row * PIXEL_SIZE + MARGIN * 2;
    
    window_width = fdf.col * 20;
    window_height = fdf.row * 20;

	if ((fdf.col * 20 > 1600) && (fdf.row * 20 > 1200))
    {
		window_width = 1600;
		window_height = 1200;
	}
	else if ((fdf.col * 20 < 800) && (fdf.row * 20 > 600))
	{
		window_width = 800;
		window_height = 600;
	}

	fdf.win = mlx_new_window(fdf.mlx, window_width, window_height, "FDF");

	int offset_x = window_width / 2;
    int offset_y = window_height / 3;
	
	apply_isometric_projection(fdf.points, fdf.row, fdf.col, offset_x, offset_y);
	
	//apply_parallel_projection(fdf.points, fdf.row, fdf.col, window_width, window_height);

	printf("selam\n");
	draw_map(fdf.mlx, fdf.win, fdf.points, fdf.row, fdf.col);
	mlx_loop(fdf.mlx);
}

