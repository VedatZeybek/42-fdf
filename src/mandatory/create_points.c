#include "fdf.h"

int	count_column(char **map)
{
	int col;
	
	char **first_row_split = ft_split(map[0], ' ');
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
		perror("File Error.");
		return (-1);
	}
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

char	**read_map(char *filename, int rows)
{
	int fd;
	char **map;
	int i;

	fd = open(filename, O_CREAT | O_RDONLY, 0644);
	i = 0;
	map = malloc(sizeof(char *) * (rows + 1)); //why ? 
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

t_point	**create_points(char **map, int col, int row)
{
	t_point	**points;
	int		i, j;
	char	**split;

	points = malloc(sizeof(t_point *) *(row + 1));
	if (!points)
		return (NULL);
	i = 0;
	while (i < row)
	{
		points[i] = malloc(sizeof(t_point) * (col + 1));
		split = ft_split(map[i], ' ');
		j = 0;
		while (j < col)
		{
			points[i][j].x = j;
			points[i][j].y = i;
			points[i][j].z = ft_atoi(split[j]);
			points[i][j].screen_x = 0;
			points[i][j].screen_y = 0;
			points[i][j].color = get_color(points[i][j].z);
			j++;
		}
		free_split(split);
		i++;
	}
	return (points);
}