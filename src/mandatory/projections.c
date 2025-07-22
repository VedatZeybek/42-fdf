#include ".././inc/fdf.h"

void apply_isometric_projection(t_fdf *fdf)
{
	int		i;
	int		j;
	float	x;
	float	y;
	float	z;

	i = 0;
	while (i < fdf->row)
	{
		j = 0;
		while (j < fdf->col)
		{
			x = fdf->points[i][j].x * fdf->scale;
			y = fdf->points[i][j].y * fdf->scale;
			z = fdf->points[i][j].z * 2.0;
			fdf->points[i][j].screen_x = (x - y) * cos( 30.0 * (3.147 / 180)) + fdf->offset_x;
			fdf->points[i][j].screen_y = (x + y) * sin( 30.0 * (3.147 / 180)) - z + fdf->offset_y;
			j++;
		}
		i++;
	}
}
