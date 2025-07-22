NAME = 			fdf

FILES =			main.c color.c isometric_projection.c create_points.c \
				error.c draw.c

BONUS_FILES =	key_handler.c parallel_projection.c

UTILS = 		get_next_line.c get_next_line_utils.c ft_atoi.c ft_split.c


FILES_PATH = 	./src/mandatory/
UTILS_PATH =	./lib/helper/
BONUS_FILES_PATH = 	./src/bonus/

SRC = 			$(addprefix $(FILES_PATH), $(FILES)) $(addprefix $(UTILS_PATH), $(UTILS))
BONUS_SRC =		$(addprefix $(BONUS_FILES_PATH), $(BONUS_FILES)) $(addprefix $(UTILS_PATH), $(UTILS))

OBJ =			$(SRC:.c=.o)
BONUS_OBJ =		$(BONUS_SRC:.c=.o)

MLX = ./minilibx-linux

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
