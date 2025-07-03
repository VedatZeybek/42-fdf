NAME = fdf

SRC = main.c other.c ...
OBJ = $(SRC:.c=.o)
MLX = ./minilibx-linux

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(MLX) -lmlx -lXext -lX11 -lm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
