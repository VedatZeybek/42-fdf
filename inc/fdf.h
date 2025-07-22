#ifndef FDF_H
# define FDF_H

#define PIXEL_SIZE 20
#define MARGIN 50

#include "fcntl.h"
#include "stdlib.h"
#include "stdio.h"
#include "../lib/helper/get_next_line.h"
#include "../lib/minilibx-linux/mlx.h"
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
	int		rotation_angle;
}	t_fdf;

int		ft_atoi(const char *str);
char	**ft_split(const char *s, char c);

int		count_column(char **map);
int		count_rows(char *filename);
char	**read_map(char *filename, int rows);
t_point	**create_points(char **map, int col, int row);

void	apply_isometric_projection(t_fdf *fdf);
void	apply_parallel_projection(t_point **points, int row, int col, int screen_width, int screen_height);
int 	get_gradient_color(int color_start, int color_end, float t);
int		get_color(int z);
void	draw_map(t_fdf *fdf);
void	free_split(char **split);
void	free_points(t_point **points);
int		handle_close(t_fdf *vars);
int		handle_key(int keycode, t_fdf *vars);
int		handle_expose(t_fdf *vars);

#endif