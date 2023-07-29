# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 13:02:34 by cwenz             #+#    #+#              #
#    Updated: 2023/07/29 17:41:45 by cwenz            ###   ########.fr        #
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

# Libft (C Library)
LIBFT_REPO			:= https://github.com/RealConrad/42c-library.git
LIBFT				:= libraries/42c-library/libft.a
C_LIBRARY_MAKE		:= make -C libraries/42c-library
C_LIBRARY_FCLEAN	:= make fclean -C libraries/42c-library

# MLX
MLX_PATH			:= libraries/MLX42
MLX					:= $(MLX_PATH)/build/libmlx42.a
MLX_FLAGS			:= ./$(MLX_PATH)/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/$(BREW)/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit

# Command to remove files
RM					:= rm -f

# Source file directories
SRC_DIR				:= ./src/
ANIMATION_DIR		:= ./src/animation/
COLLECTABLE_DIR		:= ./src/collectable/
ERROR_DIR			:= ./src/error/
INIT_DIR			:= ./src/initialize/
INPUT_DIR			:= ./src/input/
MAP_DIR				:= ./src/map/
MOB_DIR				:= ./src/mob/
UTILS_DIR			:= ./src/utils/

# Source files
SRC_FILES			:= main.c
ANIMATION_FILES		:= animation.c animation_utils.c
COLLECTABLE_FILES	:= collectables.c collectables_utils.c
ERROR_FILES			:= error.c
INIT_FILES			:= initialize.c
INPUT_FILES			:= handle_input.c input_utils.c
MAP_FILES			:= map.c map_utils.c check_map.c
MOB_FILES			:= player.c player_utils.c
UTIL_FILES			:= utils.c		

SRC 				+= $(addprefix $(SRC_DIR), $(SRC_FILES))
SRC					+= $(addprefix $(ANIMATION_DIR), $(ANIMATION_FILES))
SRC					+= $(addprefix $(COLLECTABLE_DIR), $(COLLECTABLE_FILES))
SRC 				+= $(addprefix $(ERROR_DIR), $(ERROR_FILES))
SRC					+= $(addprefix $(INIT_DIR), $(INIT_FILES))
SRC					+= $(addprefix $(INPUT_DIR), $(INPUT_FILES))
SRC					+= $(addprefix $(MAP_DIR), $(MAP_FILES))
SRC					+= $(addprefix $(MOB_DIR), $(MOB_FILES))
SRC					+= $(addprefix $(UTILS_DIR), $(UTIL_FILES))

# Object files
OBJ					:= $(SRC:.c=.o)

# Default target
all: clone $(NAME)

$(NAME): $(SRC) $(MLX)
	@$(C_LIBRARY_MAKE)
	@$(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

# Build MLX library
$(MLX):
	@cd $(MLX_PATH) && cmake -B build && cmake --build build -j4

clone:
	@if [ ! -d "libraries/42c-library" ]; then \
		cd libraries && git clone $(LIBFT_REPO); \
	fi

pull:
	@if [ -d "libraries/42c-library" ]; then \
		cd libraries/42c-library && git pull; \
	else \
		make clone; \
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
Default	= "\033[39m"
GREEN	= "\033[32m"
