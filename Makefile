NAME = 				fdf
BONUS_NAME =		fdf_bonus

FILES =				main.c color.c isometric.c create_points.c \
					error.c draw_line.c draw_map.c

BONUS_FILES =		main_bonus.c key_handler_bonus.c parallel_bonus.c color_bonus.c \
					isometric_bonus.c create_points_bonus.c rotate_bonus.c\
					error_bonus.c draw_line_bonus.c draw_map_bonus.c \
					projection_menu.c

UTILS = 			get_next_line.c get_next_line_utils.c ft_atoi.c ft_split.c ft_atoi_base.c ft_memset.c

FILES_PATH = 		./src/mandatory/
UTILS_PATH =		./lib/helper/
BONUS_FILES_PATH = 	./src/bonus/

MINILIBX	=		lib/minilibx-linux/libmlx_Linux.a


SRC = 				$(addprefix $(FILES_PATH), $(FILES)) $(addprefix $(UTILS_PATH), $(UTILS))
BONUS_SRC =			$(addprefix $(BONUS_FILES_PATH), $(BONUS_FILES)) $(addprefix $(UTILS_PATH), $(UTILS))

OBJ =				$(SRC:.c=.o)
BONUS_OBJ =			$(BONUS_SRC:.c=.o)

CC =				cc
CFLAGS =			-Wall -Wextra -Werror

MAPS_DIR = test_maps
MAPS_REPO = https://github.com/VedatZeybek/fdf-maps.git


%.o: %.c
	@$(if $(COMPILE_MSG),,$(eval COMPILE_MSG := shown)@echo "Compiling fdf files...")
	@$(CC) $(CFLAGS) -c $< -o $@


all: $(NAME)


$(NAME): $(MINILIBX) $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CC) $(OBJ) $(MINILIBX) -L./lib/minilibx-linux -lmlx -lX11 -lXext -lm -o $(NAME)

$(MINILIBX):
		@git clone https://github.com/42Paris/minilibx-linux.git lib/minilibx-linux
		@make -C lib/minilibx-linux

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	@echo "Linking $(BONUS_NAME)..."
	@$(CC) $(BONUS_OBJ) $(MINILIBX) -L./lib/minilibx-linux -lmlx -lX11 -lXext -lm -o $(BONUS_NAME)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	@echo "Removing executables..."
	@rm -rf $(NAME) $(BONUS_NAME)

re: fclean all

test: $(MAPS_DIR)

$(MAPS_DIR):
	@echo "Cloning test maps..."
	@git clone $(MAPS_REPO) $(MAPS_DIR)

.PHONY: all bonus clean fclean re test