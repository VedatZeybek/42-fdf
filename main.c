#include "./minilibx-linux/mlx.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdio.h"
#include "./gnl/get_next_line.h"
#include "fdf.h"
#include <stdlib.h>
#include <math.h>


t_point **create_points(char **map, int rows, int cols)
{
	t_point **points = malloc(sizeof(t_point *) * rows);
	for (int i = 0; i < rows; i++)
	{
		points[i] = malloc(sizeof(t_point) * cols);
		char **z_values = ft_split(map[i], ' ');
		for (int j = 0; j < cols; j++)
		{
			points[i][j].x = j;
			points[i][j].y = i;
			points[i][j].z = ft_atoi(z_values[j]);
			points[i][j].screen_x = 0;
			points[i][j].screen_y = 0;
		}
	}
	return points;
}

void apply_projection(t_point *p)
{
	float angle = 30 * 3.14 / 180.0;

	int old_x = p->x;
	int old_y = p->y;
	int z = p->z;

	int scale = 30;											  // büyütme
	p->screen_x = (old_x - old_y) * cos(angle) * scale + 400; // orta ekran
	p->screen_y = (old_x + old_y) * sin(angle) * scale - z * 3 + 200;
}

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

void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx + dy;

	while (1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0xFFFFFF); // Beyaz piksel

		if (x0 == x1 && y0 == y1)
			break;

		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
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
				draw_line(mlx, win,
						  points[y][x].screen_x, points[y][x].screen_y,
						  points[y][x + 1].screen_x, points[y][x + 1].screen_y);

			if (y < rows - 1)
				draw_line(mlx, win,
						  points[y][x].screen_x, points[y][x].screen_y,
						  points[y + 1][x].screen_x, points[y + 1][x].screen_y);
		}
	}
}

int count_cols(char *line)
{
	char **tokens = ft_split(line, ' ');
	int i = 0;
	while (tokens[i])
		i++;
	return i;
}
int close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}


int main()
{
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, 1000, 800, "Fdf");
	
	char **map = read_map("map.fdf", 11);
	if (!map)
		return (1);

	int cols = count_cols(map[0]); // otomatik kolonu hesapla

	t_point **points = create_points(map, 11, cols);

	for (int y = 0; y < 11; y++)
		for (int x = 0; x < cols; x++)
			apply_projection(&points[y][x]);

	draw_map(mlx, win, points, 11, cols);
	mlx_hook(win, 17, 0, close_window, NULL); // X tuşunu yakala
	mlx_loop(mlx);

	return 0;
}
