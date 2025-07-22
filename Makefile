NAME = fdf

SRC = main.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c ft_atoi.c ft_split.c color.c projections.c
OBJ = $(SRC:.c=.o)
MLX = ./minilibx-linux

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
