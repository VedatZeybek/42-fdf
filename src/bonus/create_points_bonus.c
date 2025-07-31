#include "../../inc/fdf_bonus.h"

int	count_column(char **map)
{
	int		col;
	char	**first_row_split;

	first_row_split = ft_split(map[0], ' ');
	col = 0;
	while (first_row_split[col])
		col++;
	free_split(first_row_split);
	return (col);
}

int	count_rows(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		exit(EXIT_FAILURE);
	}
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**read_map(char *filename, int rows)
{
	int		fd;
	char	**map;
	int		i;

	fd = open(filename, O_CREAT | O_RDONLY, 0644);
	i = 0;
	map = malloc(sizeof(char *) * (rows + 1));
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

static void	create_row_points(t_point *row_points, char *map_line,
			int col, int row_idx)
{
	char	**split;
	int		j;
	char	**parts;

	split = ft_split(map_line, ' ');
	j = 0;
	while (j < col)
	{
		parts = ft_split(split[j], ',');
		row_points[j].x = j;
		row_points[j].y = row_idx;
		row_points[j].z = ft_atoi(parts[0]);
		if (parts[1])
			row_points[j].color = ft_atoi_base(parts[1], 16);
		else
			row_points[j].color = get_color(row_points[j].z);
		row_points[j].screen_x = 0;
		row_points[j].screen_y = 0;
		free_split(parts);
		j++;
	}
	free_split(split);
}

t_point	**create_points(char **map, int col, int row)
{
	t_point	**points;
	int		i;

	points = malloc(sizeof(t_point *) * (row + 1));
	if (!points)
		return (NULL);
	i = 0;
	while (i < row)
	{
		points[i] = malloc(sizeof(t_point) * (col + 1));
		if (!points[i])
			return (NULL);
		create_row_points(points[i], map[i], col, i);
		i++;
	}
	return (points);
}
