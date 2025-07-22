#include "../../inc/fdf_bonus.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_points(t_point **points)
{
	int	i;

	if (!points)
		return ;
	i = 0;
	while (points[i])
	{
		free(points[i]);
		i++;
	}
	free(points);
}

int	handle_expose(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx, fdf->win);
	apply_isometric_projection(fdf);
	draw_map(fdf);
	return (0);
}

int	handle_close(t_fdf *vars)
{
	exit(0);
	return (0);
}
