#include "fdf.h"

static void	rotate_point_screen(t_point *p, float cos_a, float sin_a, int pivot_x, int pivot_y)
{
	int	x;
	int	y;
	int	rotated_x;
	int	rotated_y;

	x = p->screen_x - pivot_x;
	y = p->screen_y - pivot_y;
	rotated_x = (int)(x * cos_a - y * sin_a);
	rotated_y = (int)(x * sin_a + y * cos_a);
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
	cos_a = cosf(rad);
	sin_a = sinf(rad);
	i = 0;
	while (i < fdf->row)
	{
		j = 0;
		while (j < fdf->col)
		{
			rotate_point_screen(&fdf->points[i][j], cos_a, sin_a,
				fdf->offset_x, fdf->offset_y);
			j++;
		}
		i++;
	}
}


int handle_key(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 'w' || keycode == 119)
		fdf->scale += 1;
	else if ((keycode == 's' || keycode == 115) && (fdf->scale > 7))
		fdf->scale -= 1;
	else if (keycode == 65363) // Sol
		fdf->offset_x -= 20;
	else if (keycode == 65361) // Sağ
		fdf->offset_x += 20;
	else if (keycode == 65364) // Yukarı
		fdf->offset_y -= 20;
	else if (keycode == 65362) // Aşağı
		fdf->offset_y += 20;
	else if (keycode == 'a' || keycode == 97) // A tuşu - saat yönü
		fdf->rotation_angle -= 5;
	else if (keycode == 'd' || keycode == 100) // D tuşu - saatin tersi
		fdf->rotation_angle += 5;
		
	mlx_clear_window(fdf->mlx, fdf->win);
	apply_isometric_projection(fdf);
	rotate_screen_coordinates(fdf);
	draw_map(fdf);
	return (0);
}

int handle_expose(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx, fdf->win);
    apply_isometric_projection(fdf);
	rotate_screen_coordinates(fdf);
    draw_map(fdf);
	return (0);
}