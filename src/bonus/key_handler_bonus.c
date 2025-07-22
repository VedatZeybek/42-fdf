#include "../../inc/fdf_bonus.h"

void	apply_projection(t_fdf *fdf, char c)
{
	if (c == '1')
		apply_isometric_projection(fdf);
	else if (c == '2')
		apply_parallel_projection(fdf);
	else
	{
		apply_isometric_projection(fdf);
		fdf->projection_type = '1';
	}
}

static void	handle_projection_keys(int keycode, t_fdf *fdf)
{
	if (keycode == 'a' || keycode == 97)
		fdf->rotation_angle -= 5;
	else if (keycode == 'd' || keycode == 100)
		fdf->rotation_angle += 5;
	else if (keycode == 49 || keycode == '1')
		fdf->projection_type = '1';
	else if (keycode == 50 || keycode == '2')
		fdf->projection_type = '2';
}

static void	handle_movement_keys(int keycode, t_fdf *fdf)
{
	if (keycode == 'w' || keycode == 119)
		fdf->scale += 1;
	else if ((keycode == 's' || keycode == 115) && fdf->scale > 2)
		fdf->scale -= 1;
	else if (keycode == 65363)
		fdf->offset_x -= 20;
	else if (keycode == 65361)
		fdf->offset_x += 20;
	else if (keycode == 65364)
		fdf->offset_y -= 20;
	else if (keycode == 65362)
		fdf->offset_y += 20;
}

int	handle_key(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		exit(0);
	handle_movement_keys(keycode, fdf);
	handle_projection_keys(keycode, fdf);
	mlx_clear_window(fdf->mlx, fdf->win);
	apply_projection(fdf, fdf->projection_type);
	rotate_screen_coordinates(fdf);
	draw_map(fdf);
	return (0);
}
