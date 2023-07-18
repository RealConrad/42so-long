/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:57:51 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/18 14:23:21 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>

/* Include libraries */
# include "../libraries/42c-library/c_library.h" 
# include "../libraries/MLX42/include/MLX42/MLX42.h"

/* Player */
# define PLAYER_SPRITE_PATH "./assets/player/idle-down/down"
# define BLANK_PLAYER_IMAGE "./assets/player/blank.png"
# define PLAYER_SPRITE_COUNT 6
# define MOVE_SPEED 16

# define FILENAME_SIZE 50

/* Map */
# define WALL_PATH "./assets/world/wall.png"
# define GROUND_PATH "./assets/world/grass.png"
# define PIXELS 16
# define MAX_LINES 500

/* Game dimensions */
# define WIDTH 250
# define HEIGHT 250

typedef enum e_exit_type {
	SUCCESS,
	FAIL,
}	t_exit_type;

typedef struct s_player {
	mlx_texture_t	**sprites; // Array of sprites, one for each frame
	mlx_texture_t	*blank_sprite; // Used for animation to work
	mlx_image_t		*animation; // The animation image
	mlx_image_t		*img; // current image of the player
	int32_t			x; // x position of player
	int32_t			y; // y position of player
	int				curr_frame; // index of the current frame
}	t_player;

typedef struct s_map {
	char		**map_plan;
	mlx_image_t	*map_img;
}	t_map;

typedef struct s_game {
	mlx_t			*mlx;
	t_player		*player;
	t_map			*map;
}	t_game;

/* Initialize */
void	init_game(t_game *game_object, char *map_name);

/* Player */
void	init_player(t_game *game_object, int y, int x);
char	*get_player_sprites(int	sprite_index);
void	loop_player_idle_animation(void *param);

/* Map */
void	init_map(t_game *game_object, char *map_name);
void	draw_tile(t_game *game_object, int y, int x, char *path);
void	print_map(t_game *game_object); // delete me

/* Handle Input */
void	handle_input(mlx_key_data_t keydata, void *param);
bool	is_movement(mlx_key_data_t keydata);
void	count_moves();
bool	is_wall(t_game *game_object);

/* Handle errors */
void	cleanup_and_exit(t_exit_type exit_type, char *error_msg);

#endif /* SO_LONG_H */