#include "fdf.h"

int	handle_key(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 61 || keycode == 65451)
		vars->scale += 2;
	else if ((keycode == 45 || keycode == 65453) && vars->scale > 2)
		vars->scale -= 2;

	mlx_clear_window(vars->mlx, vars->win);
	apply_isometric_projection(vars->points, vars->row, vars->col, vars->offset_x, vars->offset_y, vars->scale);
	draw_map(vars->mlx, vars->win, vars->points, vars->row, vars->col);
	return (0);
}

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
	fdf.scale = 20;
	
	apply_isometric_projection(fdf.points, fdf.row, fdf.col, offset_x, offset_y, fdf.scale);
	
	//apply_parallel_projection(fdf.points, fdf.row, fdf.col, window_width, window_height);

	printf("selam\n");
	draw_map(fdf.mlx, fdf.win, fdf.points, fdf.row, fdf.col);

	mlx_key_hook(fdf.win, handle_key, &fdf);

	mlx_loop(fdf.mlx);
}

