#include "../../inc/fdf.h"

static void	parallel_projection(t_point *point, int screen_width,
			int screen_height)
{
	double	x_proj;
	double	y_proj;
	double	scale;

	x_proj = (double)point->x;
	y_proj = (double)point->y - (double)point->z * 0.9;
	scale = fmin(screen_width, screen_height) / 25.0;
	point->screen_x = (int)(screen_width / 2 + (x_proj - 10) * scale);
	point->screen_y = (int)(screen_height / 2 + (y_proj - 5) * scale);
}

void	apply_parallel_projection(t_fdf *fdf, int screen_width,
			int screen_height)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->row)
	{
		j = 0;
		while (j < fdf->col)
		{
			parallel_projection(&(fdf->points[i][j]), screen_width,
				screen_height);
			j++;
		}
		i++;
	}
}
