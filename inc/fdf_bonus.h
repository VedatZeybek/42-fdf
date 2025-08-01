/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 08:16:20 by vzeybek           #+#    #+#             */
/*   Updated: 2025/08/01 12:51:57 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# define PIXEL_SIZE 20
# define MARGIN 50

# include "fcntl.h"
# include "stdlib.h"
# include "../lib/helper/get_next_line.h"
# include "../lib/minilibx-linux/mlx.h"
# include "unistd.h"
# include "math.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	screen_x;
	int	screen_y;
	int	color;
}	t_point;

typedef struct s_fdf
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
	char	projection_type;
}	t_fdf;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	x_step;
	int	y_step;
	int	x;
	int	y;
	int	error;
	int	steps;
	int	color;
}	t_line;

int		ft_atoi(const char *str);
int		ft_atoi_base(char *str, int base);
char	**ft_split(const char *s, char c);

int		count_column(char **map);
int		count_rows(char *filename);
char	**read_map(char *filename, int rows);
t_point	**create_points(char **map, int col, int row);

void	apply_isometric_projection(t_fdf *fdf);
void	apply_parallel_projection(t_fdf *fdf);
void	rotate_screen_coordinates(t_fdf *fdf);

int		get_gradient_color(int color_start, int color_end, float t);
int		get_color(int z);
void	draw_line(t_point p0, t_point p1, void *mlx, void *mlx_window);
void	draw_map(t_fdf *fdf);
void	free_split(char **split);
void	free_points(t_point **points, int rows);
void	free_mlx_simple(t_fdf *fdf);
int		handle_key(int keycode, t_fdf *vars);
void	display_projection_menu(t_fdf *fdf);
void	*ft_memset(void *buffer, int value, size_t num);

#endif