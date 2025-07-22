#include "../../inc/fdf.h"

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
	float	cos_a;
	float	sin_a;

	rad = fdf->rotation_angle * 3.14 / 180.0f;
	cos_a = cos(rad);
	sin_a = sin(rad);
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

