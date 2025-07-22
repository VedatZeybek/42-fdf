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


int	handle_close(t_fdf *vars)
{
	exit(0);
	return (0);
}
