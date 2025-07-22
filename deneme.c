#include "./minilibx-linux/mlx.h"
#include "fdf.h"
#include "fcntl.h"
#include "stdlib.h"
#include "stdio.h"
#include "./gnl/get_next_line.h"
#include "unistd.h"
#include "math.h"

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

int	count_rows(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("File Error.");
		return (-1);
	}
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

char	**read_map(char *filename, int rows)
{
	int fd;
	char **map;
	int i;

	fd = open(filename, O_CREAT | O_RDONLY, 0644);
	i = 0;
	map = malloc(sizeof(char *) * (rows + 1)); //why ? 
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

t_point	**create_points(char **map, int col, int row)
{
	t_point	**points;
	int		i, j;
	char	**split;

	points = malloc(sizeof(t_point *) * row);
	if (!points)
		return (NULL);
	i = 0;
	while (i < row)
	{
		points[i] = malloc(sizeof(t_point) * col);
		split = ft_split(map[i], ' ');
		j = 0;
		while (j < col)
		{
			points[i][j].x = j;
			points[i][j].y = i;
			points[i][j].z = ft_atoi(split[j]);
			points[i][j].screen_x = 0;
			points[i][j].screen_y = 0;
			j++;
		}
		free_split(split);
		i++;
	}
	return (points);
}

void	apply_projection(t_point **points, int row, int col)
{
	int		i;
	int		j;
	float	angle;
	int		x;
	int		y;
	int		z;

	angle = 0.523599;
	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			x = points[i][j].x;	
			y = points[i][j].y;	
			z = points[i][j].z;

			points[i][j].screen_x = x;
			points[i][j].screen_y = y + 0.10 * z;

			j++;
		}
		i++;
	}	
}


void	draw_line(t_point point0, t_point point1, void	*mlx, void	*mlx_window)
{
	int	i;
	int	x0;
	int	y0;
	int x_diff;
	int y_diff;
	int	diversion_max;
	
	i = 0;
	x0 = point0.screen_x;
	y0 = point0.screen_y;

	x_diff = x0 - point1.screen_x;
	y_diff = y0 - point1.screen_y;

	diversion_max = fmax(fabs(x_diff), fabs(y_diff));

	x_diff = x_diff / diversion_max;
	y_diff = y_diff / diversion_max;

	while (point0.screen_x - x0 || point0.screen_y - y0)
	{
		mlx_pixel_put(mlx, mlx_window, x0, y0,  0x0000FF);
		x0 = x0 + x_diff;
		y0 = y0 + y_diff;
	}	
}

void draw_map(void *mlx, void *win, t_point **points, int rows, int cols)
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (x < cols - 1)
				draw_line(points[y][x], points[y + 1][x], mlx, win);
			if (y < rows - 1)
				draw_line(points[y][x], points[y][x + 1], mlx, win);
		}
	}
}

int main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_window;
	char	**map;
	int		row;
	int		col;
	t_point	**points;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 800, 600, "Hello world!");
	row = count_rows(argv[1]);
	map = read_map(argv[1], row);
	col = ft_strlen(map[0]);
	printf("selam\n");

	points = create_points(map, col, row);
	
	apply_projection(points, row, col);
	
	draw_map(mlx, mlx_window, points, row, col);
	mlx_loop(mlx);
}

