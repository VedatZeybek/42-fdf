#ifndef FDF_H
# define FDF_H

#define PIXEL_SIZE 20
#define MARGIN 50

#include "fcntl.h"
#include "stdlib.h"
#include "stdio.h"
#include "./gnl/get_next_line.h"
#include "./minilibx-linux/mlx.h"
#include "unistd.h"
#include "math.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	screen_x;
	int	screen_y;
	int	color;
}	t_point;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		row;
	int		col;
	char	**map;
	t_point	**points;
	int		offset_x;
	int		offset_y;
	int		scale;
}	t_vars;

int		ft_atoi(const char *str);
char	**ft_split(const char *s, char c);

int		count_column(char **map);
int		count_rows(char *filename);
char	**read_map(char *filename, int rows);
t_point	**create_points(char **map, int col, int row);

void 	apply_isometric_projection(t_point **points, int row, int col, int offset_x, int offset_y, int scale);
void	apply_parallel_projection(t_point **points, int row, int col, int screen_width, int screen_height);
int 	get_gradient_color(int color_start, int color_end, float t);
int		get_color(int z);
void	draw_map(void *mlx, void *win, t_point **points, int rows, int cols);
void	free_split(char **split);
int		handle_close(t_vars *vars);

#endif