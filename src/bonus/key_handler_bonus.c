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

int	handle_key(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 'w' || keycode == 119)
		fdf->scale += 1;
	else if ((keycode == 's' || keycode == 115) && (fdf->scale > 7))
		fdf->scale -= 1;
	else if (keycode == 65363)
		fdf->offset_x -= 20;
	else if (keycode == 65361)
		fdf->offset_x += 20;
	else if (keycode == 65364)
		fdf->offset_y -= 20;
	else if (keycode == 65362)
		fdf->offset_y += 20;
	else if (keycode == 'a' || keycode == 97)
		fdf->rotation_angle -= 5;
	else if (keycode == 'd' || keycode == 100)
		fdf->rotation_angle += 5;
	mlx_clear_window(fdf->mlx, fdf->win);
	apply_isometric_projection(fdf);
	rotate_screen_coordinates(fdf);
	draw_map(fdf);
	return (0);
}
