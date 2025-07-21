NAME = fdf

SRC = deneme.c
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
