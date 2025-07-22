#ifndef FDF_H
# define FDF_H


#define PIXEL_SIZE 20
#define MARGIN 50

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	screen_x;
	int	screen_y;
}	t_point;



int		ft_atoi(const char *str);
char	**ft_split(const char *s, char c);


#endif