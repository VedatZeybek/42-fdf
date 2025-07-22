#include "../../inc/fdf.h"

static void	parallel_projection(t_point *point, t_fdf *fdf)
{
	double	x_proj;
	double	y_proj;
	double	scale;

	x_proj = (double)point->x;
	y_proj = (double)point->y - (double)point->z * 0.2;
	scale = fdf->scale;
	point->screen_x = (int)(fdf->offset_x + (x_proj - 10) * scale);
	point->screen_y = (int)(fdf->offset_y + (y_proj - 5) * scale);
}

void	apply_parallel_projection(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->row)
	{
		j = 0;
		while (j < fdf->col)
		{
			parallel_projection(&(fdf->points[i][j]), fdf);
			j++;
		}
		i++;
	}
}
