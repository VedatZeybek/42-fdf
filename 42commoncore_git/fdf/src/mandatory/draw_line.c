/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 08:14:40 by vzeybek           #+#    #+#             */
/*   Updated: 2025/08/01 08:14:41 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

static void	init_line_data(t_point p0, t_point p1, t_line *line)
{
	line->dx = abs(p1.screen_x - p0.screen_x);
	line->dy = abs(p1.screen_y - p0.screen_y);
	if (p0.screen_x < p1.screen_x)
		line->x_step = 1;
	else
		line->x_step = -1;
	if (p0.screen_y < p1.screen_y)
		line->y_step = 1;
	else
		line->y_step = -1;
	line->x = p0.screen_x;
	line->y = p0.screen_y;
	line->error = line->dx - line->dy;
	if (line->dx > line->dy)
		line->steps = line->dx;
	else
		line->steps = line->dy;
	line->color = 0;
}

static void	calculate_next_pixel(t_line *line)
{
	int	error2;

	error2 = 2 * line->error;
	if (error2 > -(line->dy))
	{
		line->error -= line->dy;
		line->x += line->x_step;
	}
	if (error2 < line->dx)
	{
		line->error += line->dx;
		line->y += line->y_step;
	}
}

static void	draw_gradient_pixel(t_line *line, t_point p0, t_point p1, int step)
{
	float	t;

	if (line->steps == 0)
		t = 0.0;
	else
		t = (float)step / line->steps;
	line->color = get_gradient_color(p0.color, p1.color, t);
}

static int	put_pixel_and_check(t_line *line, t_point p1, void *mlx, void *win)
{
	mlx_pixel_put(mlx, win, line->x, line->y, line->color);
	return (line->x == p1.screen_x && line->y == p1.screen_y);
}

void	draw_line(t_point p0, t_point p1, void *mlx, void *mlx_window)
{
	t_line	line;
	int		i;

	init_line_data(p0, p1, &line);
	i = 0;
	while (i <= line.steps)
	{
		draw_gradient_pixel(&line, p0, p1, i);
		if (put_pixel_and_check(&line, p1, mlx, mlx_window))
			break ;
		calculate_next_pixel(&line);
		i++;
	}
}
