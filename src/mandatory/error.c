/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 08:14:45 by vzeybek           #+#    #+#             */
/*   Updated: 2025/08/01 13:03:57 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_points(t_point **points, int rows)
{
	int	i;

	if (!points)
		return ;
	i = 0;
	while (i < rows)
	{
		free(points[i]);
		i++;
	}
	free(points);
}

void	free_mlx_simple(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx, fdf->win);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
		mlx_destroy_display(fdf->mlx);
	// if (fdf->img)
	// 	mlx_destroy_image(fdf->img, NULL);
}

int	handle_close(t_fdf *fdf)
{
	free_points(fdf->points, fdf->row);
	free_split(fdf->map);
	free_mlx_simple(fdf);
	free(fdf->mlx);
	exit(0);
}
