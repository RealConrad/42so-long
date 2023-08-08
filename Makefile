# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 13:02:34 by cwenz             #+#    #+#              #
#    Updated: 2023/08/08 13:11:48 by cwenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the binary executable
NAME				:= so_long

# Username and brew location
USER				:= cwenz
BREW				:= .brew

# Compiler and flags
#  -fsanitize=address -g
CC					:= cc
CFLAGS				:= -Wall -Werror -Wextra
INCLUDES			:= -I./includes

# Submodules:
## Libft
LIBFT_PATH			:= libraries/42c-library
LIBFT				:= libraries/42c-library/libft.a
C_LIBRARY_MAKE		:= make -C libraries/42c-library
C_LIBRARY_FCLEAN	:= make fclean -C libraries/42c-library
## MLX
MLX_PATH			:= libraries/MLX42
MLX					:= $(MLX_PATH)/build/libmlx42.a
MLX_FLAGS			:= ./$(MLX) -Iinclude -lglfw -L"/Users/$(USER)/$(BREW)/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit

# Command to remove files
RM					:= rm -f

# Source file directories
SRC_DIR				:= ./src/
ANIMATION_DIR		:= ./src/animation/
COLLECTABLE_DIR		:= ./src/collectable/
ERROR_DIR			:= ./src/error/
EXIT_DIR			:= ./src/exit/
FREE_DIR			:= ./src/free/
HUD_DIR				:= ./src/hud/
INIT_DIR			:= ./src/initialize/
INPUT_DIR			:= ./src/input/
MAP_DIR				:= ./src/map/
MOB_DIR				:= ./src/mob/
TRAP_DIR			:= ./src/trap/
UTILS_DIR			:= ./src/utils/

# Source files
SRC_FILES			:= main.c
ANIMATION_FILES		:= animation.c animation_utils.c trap_animation_utils.c
COLLECTABLE_FILES	:= collectables.c collectables_utils.c
ERROR_FILES			:= error.c
EXIT_FILES			:= exit.c
FREE_FILES			:= free.c free_utils.c free_enemy.c
HUD_FILES			:= hud.c hud_utils.c player_dialogue.c
INIT_FILES			:= initialize.c
INPUT_FILES			:= handle_input.c input_utils.c
MAP_FILES			:= map.c map_utils.c check_map.c check_map_utils.c check_map_utils2.c is_map_solvable.c
MOB_FILES			:= player.c player_death.c mimic.c enemy.c
TRAP_FILES			:= trap.c trap_utils.c
UTIL_FILES			:= utils.c utils2.c

SRC 				+= $(addprefix $(SRC_DIR), $(SRC_FILES))
SRC					+= $(addprefix $(ANIMATION_DIR), $(ANIMATION_FILES))
SRC					+= $(addprefix $(COLLECTABLE_DIR), $(COLLECTABLE_FILES))
SRC 				+= $(addprefix $(ERROR_DIR), $(ERROR_FILES))
SRC 				+= $(addprefix $(EXIT_DIR), $(EXIT_FILES))
SRC 				+= $(addprefix $(FREE_DIR), $(FREE_FILES))
SRC 				+= $(addprefix $(HUD_DIR), $(HUD_FILES))
SRC					+= $(addprefix $(INIT_DIR), $(INIT_FILES))
SRC					+= $(addprefix $(INPUT_DIR), $(INPUT_FILES))
SRC					+= $(addprefix $(MAP_DIR), $(MAP_FILES))
SRC					+= $(addprefix $(MOB_DIR), $(MOB_FILES))
SRC					+= $(addprefix $(TRAP_DIR), $(TRAP_FILES))
SRC					+= $(addprefix $(UTILS_DIR), $(UTIL_FILES))

# Object files
OBJ					:= $(SRC:.c=.o)

# Default target
all: init-submodules $(NAME)

$(NAME): $(OBJ) $(MLX)
	@$(C_LIBRARY_MAKE)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo $(GREEN)"Linking $(NAME)";$(DEFAULT)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build MLX library
$(MLX):
	@cd $(MLX_PATH) && cmake -B build && cmake --build build -j4

# Init submodules
init-submodules:
	@if [ -z "$(shell ls -A $(MLX_PATH))" ]; then \
		@echo -e $(GREEN)"Initializing and updating MLX submodule..."$(DEFAULT); \
		git submodule init $(MLX_PATH); \
		git submodule update $(MLX_PATH); \
	fi
	@if [ -z "$(shell ls -A $(LIBFT_PATH))" ]; then \
		@echo -e $(GREEN)"Initializing and updating LIBFT submodule..."$(DEFAULT); \
		git submodule init $(LIBFT_PATH); \
		git submodule update $(LIBFT_PATH); \
	fi

# Remove all object files
clean:
	@$(RM) $(OBJ)

# Remove all generated files
fclean: clean
	@$(C_LIBRARY_FCLEAN)
	@$(RM) $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clone clean fclean re

# Colours to make it look nice :)
DEFAULT	= "\033[39m"
GREEN	= "\033[32m"
