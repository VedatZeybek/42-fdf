NAME = 			fdf
BONUS_NAME =	fdf_bonus

FILES =			main.c color.c isometric.c create_points.c \
				error.c draw.c

BONUS_FILES =	main_bonus.c key_handler_bonus.c parallel_bonus.c color_bonus.c \
				isometric_bonus.c create_points_bonus.c \
				error_bonus.c draw_bonus.c

UTILS = 		get_next_line.c get_next_line_utils.c ft_atoi.c ft_split.c


FILES_PATH = 	./src/mandatory/
UTILS_PATH =	./lib/helper/
BONUS_FILES_PATH = 	./src/bonus/

SRC = 			$(addprefix $(FILES_PATH), $(FILES)) $(addprefix $(UTILS_PATH), $(UTILS))
BONUS_SRC =		$(addprefix $(BONUS_FILES_PATH), $(BONUS_FILES)) $(addprefix $(UTILS_PATH), $(UTILS))

OBJ =			$(SRC:.c=.o)
BONUS_OBJ =		$(BONUS_SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


bonus: $(BONUS_NAME)
	
$(BONUS_NAME): $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(BONUS_NAME)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
