#include "../../inc/fdf.h"


static void	display_projection_menu(t_fdf *fdf)
{
	char	*text;

	if (fdf->projection_type == '1')
		text = "Projection: Isometric (press 1 or 2)";
	else if (fdf->projection_type == '2')
		text = "Projection: Parallel  (press 1 or 2)";
	else
		text = "Projection: Unknown";

	mlx_string_put(fdf->mlx, fdf->win, 20, 30, 0xFFFFFF, text);
}


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
	display_projection_menu(fdf);
}
