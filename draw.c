#include "fdf.h"

static void draw_line(t_point p0, t_point p1, void *mlx, void *mlx_window)
{
	int dx = abs(p1.screen_x - p0.screen_x);
	int dy = abs(p1.screen_y - p0.screen_y);
	int x_step = (p0.screen_x < p1.screen_x) ? 1 : -1;
	int y_step = (p0.screen_y < p1.screen_y) ? 1 : -1;

	int x = p0.screen_x;
	int y = p0.screen_y;
	int error = dx - dy;
	int steps = (dx > dy) ? dx : dy;

	for (int i = 0; i <= steps; i++)
	{
		float t = (steps == 0) ? 0.0 : (float)i / steps;
		int color = get_gradient_color(p0.color, p1.color, t);
		mlx_pixel_put(mlx, mlx_window, x, y, color);

		if (x == p1.screen_x && y == p1.screen_y)
			break;

		int error2 = 2 * error;
		if (error2 > -dy)
		{
			error -= dy;
			x += x_step;
		}
		if (error2 < dx)
		{
			error += dx;
			y += y_step;
		}
	}
}

void draw_map(t_fdf *fdf)
{
	for (int y = 0; y < fdf->row; y++)
	{
		for (int x = 0; x < fdf->col; x++)
		{
			if (x < fdf->col - 1)
			draw_line(fdf->points[y][x], fdf->points[y][x + 1], fdf->mlx, fdf->win);
			if (y < fdf->row - 1)
			draw_line(fdf->points[y][x], fdf->points[y + 1][x], fdf->mlx, fdf->win);
		}
	}
}