#include "fdf.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
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
		return;
	i = 0;
	while (points[i])
	{
		free(points[i]);
		i++;
	}
	free(points);
}


int	handle_close(t_fdf *vars)
{
	exit(0);
	return (0);
}
