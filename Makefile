# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 13:02:34 by cwenz             #+#    #+#              #
#    Updated: 2023/07/10 14:49:23 by cwenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the binary executable
NAME				:= so_long

# Username and brew location
USER				:= cwenz
BREW				:= homebrew

# Compiler and flags
CC					:= cc
CFLAGS				:= -Wall -Werror -Wextra -I./includes

# Libft (C Library)
LIBFT_REPO			:= https://github.com/RealConrad/42c-library.git
LIBFT				:= libraries/42c-library/libft.a
C_LIBRARY_MAKE		:= make -C libraries/42c-library
C_LIBRARY_FCLEAN	:= make fclean -C libraries/42c-library

# MLX
MLX_PATH			:= libraries/MLX42
MLX					:= $(MLX_PATH)/build/libmlx42.a
MLX_FLAGS			:= ./libraries/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/$(BREW)/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit

# Command to remove files
RM					:= rm -f

# Source file directories
SRC_DIR				:= ./src/

# Source files
SRC_FILES			:= main.c

SRC 				+= $(addprefix $(SRC_DIR), $(SRC_FILES))

# Object files
OBJ					:= $(SRC:.c=.o)

# Default target
all: clone $(NAME)

$(NAME): $(SRC) $(MLX)
	@$(C_LIBRARY_MAKE)
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

# Build MLX library
$(MLX):
	@cd $(MLX_PATH)
	@cmake -B build
	@cmake --build build -j4

clone:
	@if [ ! -d "libraries/42c-library" ]; then \
		echo $(GREEN)"Cloning c-library"$(DEFAULT); \
		cd libraries && git clone $(LIBFT_REPO); \
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
DEFAULT                 = "\033[39m"
GREEN                   = "\033[32m"
