#include "fdf.h"

static void	parallel_projection(t_point *point, int screen_width, int screen_height)
{
	double	x_proj, y_proj;
	double	scale;
	
	x_proj = (double)point->x;
	y_proj = (double)point->y - (double)point->z * 0.9;
	
	scale = fmin(screen_width, screen_height) / 25.0;
	
	point->screen_x = (int)(screen_width / 2 + (x_proj - 10) * scale);
	point->screen_y = (int)(screen_height / 2 + (y_proj - 5) * scale);
}

void	apply_parallel_projection(t_point **points, int row, int col, int screen_width, int screen_height)
{
	int	i, j;
	
	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			parallel_projection(&points[i][j], screen_width, screen_height);
			j++;
		}
		i++;
	}
}

void apply_isometric_projection(t_fdf *fdf)
{
	int		i, j;
	float	z_scale = 2.0;

	float	angle = 30.0 * (3.147 / 180);  // Dereceyi radyana çevir: 30° = π/6

	float	cos_angle = cos(angle);  // ≈ 0.866
	float	sin_angle = sin(angle);  // ≈ 0.5

	for (i = 0; i < fdf->row; i++)
	{
		for (j = 0; j < fdf->col; j++)
		{
			float x = fdf->points[i][j].x * fdf->scale;
			float y = fdf->points[i][j].y * fdf->scale;
			float z = fdf->points[i][j].z * z_scale;

			fdf->points[i][j].screen_x = (x - y) * cos_angle + fdf->offset_x;
			fdf->points[i][j].screen_y = (x + y) * sin_angle - z + fdf->offset_y;
		}
	}
}