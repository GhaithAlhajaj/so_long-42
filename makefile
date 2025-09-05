NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
SRC_FILES = layout.c draw_game.c free_exit.c init_core.c key_control.c load_map.c main.c move_logic.c validate_map.c update_frame.c valid_path.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INC_DIR = so_long.h/inc
LIBFT_DIR = libft
LIBFT = $(libft)/libft.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

LIB = -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

all: $(OBJ_DIR) $(LIBFT)  $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
