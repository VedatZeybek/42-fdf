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

void apply_projection(t_point **points, int row, int col, int offset_x, int offset_y)
{
	int	i;
	int	j;
	int	scale = 20;


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
	int x = point0.screen_x;
	int y = point0.screen_y;
	int x_step = (point0.screen_x < point1.screen_x) ? 1 : -1;
	int y_step = (point0.screen_y < point1.screen_y) ? 1 : -1;
	int error;
	int error2;

	error = dx - dy;
	while (1)
	{
		mlx_pixel_put(mlx, mlx_window, x, y, 0x0000FF);
		if (x == point1.screen_x && y == point1.screen_y)
			break;
		error2 = 2 * error;
		if (error2 > -dy)
		{
			error -= dy;
			x += x_step;
		}
		if (error2 < dx)
		{
			error += dx;
			y += y_step;
		}
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

void	parallel_projection(t_point *point, int screen_width, int screen_height)
{
	double	x_proj, y_proj;
	double	scale;
	
	x_proj = (double)point->x;
	y_proj = (double)point->y - (double)point->z * 1;
	
	scale = fmin(screen_width, screen_height) / 25.0;
	
	point->screen_x = (int)(screen_width / 2 + (x_proj - 10) * scale);
	point->screen_y = (int)(screen_height / 2 + (y_proj - 5) * scale);
}

void	apply_parallel_projection(t_point **points, int row, int col, int screen_width, int screen_height)
{
	int	i, j;
	
	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			parallel_projection(&points[i][j], screen_width, screen_height);
			j++;
		}
		i++;
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
	row = count_rows(argv[1]);
	map = read_map(argv[1], row);
	col = calculate_column(map);
	
	points = create_points(map, col, row);
	
	int window_width = col * PIXEL_SIZE + MARGIN * 2;
    int window_height = row * PIXEL_SIZE + MARGIN * 2;
    
    window_width = (col * 20 > 1920) ? 1920 : col * 20;
    window_height = (row * 20 > 1200) ? 1200 : row * 20;
    
	window_width = (col * 20 < 800) ? 800 : col * 20;
    window_height = (row * 20 < 600) ? 600 : row * 20;
    
	mlx_window = mlx_new_window(mlx, window_width, window_height, "FDF");

	int offset_x = window_width / 2;
    int offset_y = window_height / 3;
	
	//apply_projection(points, row, col, offset_x, offset_y);
	
	//apply_parallel_projection(points, row, col, window_width, window_height);

	draw_map(mlx, mlx_window, points, row, col);
	mlx_loop(mlx);
}

