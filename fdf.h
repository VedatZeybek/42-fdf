#ifndef FDF_H
# define FDF_H


#define PIXEL_SIZE 20
#define MARGIN 50

#include "fcntl.h"
#include "stdlib.h"
#include "stdio.h"
#include "./gnl/get_next_line.h"
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



int		ft_atoi(const char *str);
char	**ft_split(const char *s, char c);
void	apply_isometric_projection(t_point **points, int row, int col, int offset_x, int offset_y);
void	apply_parallel_projection(t_point **points, int row, int col, int screen_width, int screen_height);
int 	get_gradient_color(int color_start, int color_end, float t);
int		get_color(int z);

#endif