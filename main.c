#include "./minilibx-linux/mlx.h"
#include "fdf.h"

void draw_line(t_point p0, t_point p1, void *mlx, void *mlx_window)
{
	int dx = abs(p1.screen_x - p0.screen_x);
	int dy = abs(p1.screen_y - p0.screen_y);
	int x_step = (p0.screen_x < p1.screen_x) ? 1 : -1;
	int y_step = (p0.screen_y < p1.screen_y) ? 1 : -1;

	int x = p0.screen_x;
	int y = p0.screen_y;
	int error = dx - dy;
	int steps = (dx > dy) ? dx : dy;

	for (int i = 0; i <= steps; i++)
	{
		float t = (steps == 0) ? 0.0 : (float)i / steps;
		int color = get_gradient_color(p0.color, p1.color, t);
		mlx_pixel_put(mlx, mlx_window, x, y, color);

		if (x == p1.screen_x && y == p1.screen_y)
			break;

		int error2 = 2 * error;
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
    
    window_width = col * 20;
    window_height = row * 20;

	if ((col * 20 > 1600) && (row * 20 > 1200))
    {
		window_width = 1600;
		window_height = 1200;
	}
	else if ((col * 20 < 800) && (row * 20 > 600))
	{
		window_width = 800;
		window_height = 600;
	}

	mlx_window = mlx_new_window(mlx, window_width, window_height, "FDF");

	int offset_x = window_width / 2;
    int offset_y = window_height / 3;
	
	apply_isometric_projection(points, row, col, offset_x, offset_y);
	
	//apply_parallel_projection(points, row, col, window_width, window_height);

	printf("selam\n");
	draw_map(mlx, mlx_window, points, row, col);
	mlx_loop(mlx);
}

