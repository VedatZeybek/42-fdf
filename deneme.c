#include "./minilibx-linux/mlx.h"
#include "fdf.h"
#include "fcntl.h"
#include "stdlib.h"

char **read_map(char *filename, int rows)
{
	int fd;
	char **map;
	int i;

	fd = open(filename, O_CREAT | O_RDONLY, 0644);
	i = 0;
	map = malloc(sizeof(char *) * rows + 1);
	if (!map)
		return (NULL);
	while (i < rows)
	{
		if (!map)
			return (NULL);
		map[i] = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}


void printf_map(char **map)
{
	int i = 0;

	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_window;
	char	**map;
	
	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 800, 600, "Hello world!");
	map = read_map(argv[1], )

	int	i = 400;
	int	j = 300;
	
	while (i < 500)
	{
		mlx_pixel_put(mlx, mlx_window, i, j, 0x0000FF);
		i++;
		j++;
	}
	
	
	
	mlx_loop(mlx);
}