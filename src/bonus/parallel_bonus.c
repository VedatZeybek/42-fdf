#include "../../inc/fdf_bonus.h"

static void	parallel_projection(t_point *point, t_fdf *fdf)
{
	double	x_proj;
	double	y_proj;
	double	center_x;
	double	center_y;
	double	scale;

	scale = fdf->scale;
	center_x = (fdf->col - 1) / 2.0;
	center_y = (fdf->row - 1) / 2.0;
	x_proj = (double)point->x - center_x;
	y_proj = (double)point->y - center_y - point->z * 0.2;
	point->screen_x = (int)(fdf->offset_x + x_proj * scale);
	point->screen_y = (int)(fdf->offset_y + y_proj * scale);
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
