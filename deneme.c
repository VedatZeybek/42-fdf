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

	points = malloc(sizeof(t_point *) *(row + 1));
	if (!points)
		return (NULL);
	i = 0;
	while (i < row)
	{
		points[i] = malloc(sizeof(t_point) * (col + 1));
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

void apply_projection(t_point **points, int row, int col)
{
    int i, j;
    int scale = 20;
    int offset_x = 400;
    int offset_y = 300;
    
    i = 0;
    while (i < row)
    {
        j = 0;
        while (j < col)
        {
            int x = points[i][j].x;
            int y = points[i][j].y;
            int z = points[i][j].z;
            
            points[i][j].screen_x = (x - y) * scale + offset_x;
            points[i][j].screen_y = (x + y) * scale/2 - z * scale/3 + offset_y;
            
            j++;
        }
        i++;
    }
}

void draw_line(t_point point0, t_point point1, void *mlx, void *mlx_window)
{
	int dx = abs(point1.screen_x - point0.screen_x);
	int dy = abs(point1.screen_y - point0.screen_y);
	int steps = (dx > dy) ? dx : dy;

	float x_inc = (float)(point1.screen_x - point0.screen_x) / steps;
	float y_inc = (float)(point1.screen_y - point0.screen_y) / steps;

	float x = point0.screen_x;
	float y = point0.screen_y;

	for (int i = 0; i <= steps; i++)
	{
		mlx_pixel_put(mlx, mlx_window, (int)x, (int)y, 0x0000FF);
		x += x_inc;
		y += y_inc;
	}
}

void draw_map(void *mlx, void *win, t_point **points, int rows, int cols)
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (x < cols - 1)
			draw_line(points[y][x], points[y][x + 1], mlx, win);
			if (y < rows - 1)
			draw_line(points[y][x], points[y + 1][x], mlx, win);
		}
	}
}

int	calculate_column(char **map)
{
	int col;
	
	char **first_row_split = ft_split(map[0], ' ');
	col = 0;
	while (first_row_split[col])
	col++;
	free_split(first_row_split);
	return (col);
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
	col = calculate_column(map);
	
	points = create_points(map, col, row);
	
	apply_projection(points, row, col);
	
	printf("selam\n");
	draw_map(mlx, mlx_window, points, row, col);
	mlx_loop(mlx);
}

// void	apply_projection(t_point **points, int row, int col)
// {
// 	int		i;
// 	int		j;
// 	float	angle;
// 	int		x;
// 	int		y;
// 	int		z;

// 	angle = 0.523599;
// 	i = 0;
// 	while (i < row)
// 	{
// 		j = 0;
// 		while (j < col)
// 		{
// 			x = points[i][j].x;	
// 			y = points[i][j].y;	
// 			z = points[i][j].z;

// 			points[i][j].screen_x = x;
// 			points[i][j].screen_y = y + 0.10 * z;

// 			j++;
// 		}
// 		i++;
// 	}	
// }

// void	draw_line(t_point point0, t_point point1, void	*mlx, void	*mlx_window)
// {
	// 	int	i;
	// 	int	x0;
	// 	int	y0;
	// 	int x_diff;
	// 	int y_diff;
	// 	int	diversion_max;
	
	// 	i = 0;
	// 	x0 = point0.screen_x;
	// 	y0 = point0.screen_y;
	
	// 	x_diff = x0 - point1.screen_x;
	// 	y_diff = y0 - point1.screen_y;
	
	// 	diversion_max = fmax(fabs(x_diff), fabs(y_diff));
	
	// 	x_diff = x_diff / diversion_max;
	// 	y_diff = y_diff / diversion_max;
	
	// 	while (point0.screen_x - x0 || point0.screen_y - y0)
	// 	{
		// 		mlx_pixel_put(mlx, mlx_window, x0, y0,  0x0000FF);
		// 		x0 = x0 + x_diff;
		// 		y0 = y0 + y_diff;
		// 	}	
		// }