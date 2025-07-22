#include "../../inc/fdf.h"

void	draw_map(t_fdf *fdf)
{
	int	y;
	int	x;

	y = 0;
	while (y < fdf->row)
	{
		x = 0;
		while (x < fdf->col)
		{
			if (x < fdf->col - 1)
				draw_line(fdf->points[y][x], fdf->points[y][x + 1],
					fdf->mlx, fdf->win);
			if (y < fdf->row - 1)
				draw_line(fdf->points[y][x], fdf->points[y + 1][x],
					fdf->mlx, fdf->win);
			x++;
		}
		y++;
	}
}
