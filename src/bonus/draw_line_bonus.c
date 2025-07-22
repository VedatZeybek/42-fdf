#include "../../inc/fdf.h"

static void	init_line_data(t_point p0, t_point p1, int *params)
{
	params[0] = abs(p1.screen_x - p0.screen_x);
	params[1] = abs(p1.screen_y - p0.screen_y);
	if (p0.screen_x < p1.screen_x)
		params[2] = 1;
	else
		params[2] = -1;
	if (p0.screen_y < p1.screen_y)
		params[3] = 1;
	else
		params[3] = -1;
	params[4] = p0.screen_x;
	params[5] = p0.screen_y;
	params[6] = params[0] - params[1];
	if (params[0] > params[1])
		params[7] = params[0];
	else
		params[7] = params[1];
	params[8] = 0;
}

static void	calculate_next_pixel(int *params)
{
	int	error2;

	error2 = 2 * params[6];
	if (error2 > -params[1])
	{
		params[6] -= params[1];
		params[4] += params[2];
	}
	if (error2 < params[0])
	{
		params[6] += params[0];
		params[5] += params[3];
	}
}

static void	draw_gradient_pixel(int *params, t_point p0, t_point p1, int step)
{
	float	t;
	int		color;

	if (params[7] == 0)
		t = 0.0;
	else
		t = (float)step / params[7];
	color = get_gradient_color(p0.color, p1.color, t);
	params[8] = color;
}

static int	put_pixel_and_check(int *params, t_point p1,
			void *mlx, void *mlx_window)
{
	mlx_pixel_put(mlx, mlx_window, params[4], params[5], params[8]);
	return (params[4] == p1.screen_x && params[5] == p1.screen_y);
}

void	draw_line(t_point p0, t_point p1, void *mlx, void *mlx_window)
{
	int	params[9];
	int	i;

	init_line_data(p0, p1, params);
	i = 0;
	while (i <= params[7])
	{
		draw_gradient_pixel(params, p0, p1, i);
		if (put_pixel_and_check(params, p1, mlx, mlx_window))
			break ;
		calculate_next_pixel(params);
		i++;
	}
}
