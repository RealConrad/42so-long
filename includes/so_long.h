/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:57:51 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/30 15:06:38 by cwenz            ###   ########.fr       */
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

/* Game */
# define WIDTH 1000
# define HEIGHT 1000
# define FILENAME_SIZE 69
# define TIME_FOR_FRAME 0.1

/* Player */
# define PLAYER_SPRITE_PATH "./assets/player/idle"
# define BLANK_SPRITE "./assets/player/blank.png"
# define PLAYER_SPRITE_COUNT 4
# define PLAYER_HEIGHT_PX 64
# define PLAYER_WIDTH_PX 36

/* Map */
# define WALL_PATH "./assets/world/map/wall.png"
# define GROUND_PATH "./assets/world/map/floor.png"
# define EXIT_PATH "./assets/world/exit/exit.png"
# define TILE_PX 64
# define MAX_LINES 500

/* Collectables */
# define COLLECTABLE_PATH "./assets/world/collectables/coin"
# define COLLECTABLE_SPRITE_COUNT 4
# define COLLECTABLE_HEIGHT_PX 24
# define COLLECTABLE_WIDTH_PX 16

typedef enum e_exit_type {
	SUCCESS,
	FAIL,
}	t_exit_type;

typedef struct s_animated_mob {
	mlx_texture_t	**sprites; // Array of sprites, one for each frame
	mlx_image_t		**animated_sprite; // The animation image
	char			*sprite_path; // file path to sprites
	int				frame_skip_counter;
	int				frame_skip_amount; // Used for speed of animation
	int				curr_frame; // index of the current frame
	int				num_sprites;
	int				height;
	int				width;
	int				x;
	int				y;
}	t_animated_mob;

typedef struct s_collectables {
	t_animated_mob			*coin;
	bool					is_collected;
	struct s_collectables	*next;
	struct s_collectables	*prev;
}	t_collectables;

typedef struct s_map {
	char			**map_plan;
	mlx_image_t		*exit;
	mlx_image_t		*map_img;
	t_collectables	*collectables;
	int				num_collectables;
	int				num_lines;
}	t_map;

typedef struct s_game {
	mlx_t			*mlx;
	t_animated_mob	*player;
	t_map			*map;
}	t_game;

/* Initialize */
void	init_game(t_game *game_object, char *map_name);

/* Player */
void	init_player(t_game *game_object, int y, int x);
void	assign_player_object(t_game *game_object, int y, int x);
bool	allocate_player_object(t_animated_mob *player);

/* Collectables */
void	init_collectable(t_game *game_object, int y, int x);
bool	allocate_collectable_object(t_animated_mob *collectable);
void	assign_collectable_object(t_game *game_object, t_animated_mob *collectable, int y, int x);
void	add_collectable_node(t_game *game_object, t_collectables *new_collectable);
void	remove_collectable(t_game *game_object);

/* Animation */
void	init_animation(void	*param);
char	*get_sprites(int	sprite_index, t_animated_mob *animation_config);
void	animate_sprite(t_animated_mob *animation_config);
void	update_sprite_position(t_animated_mob *animation_config);

/* Map */
void	init_map(t_game *game_object, char *map_name);
void	draw_tile(t_game *game_object, int y, int x, char *path);
void	check_map(t_game *game_object, char *map_name);
void	print_map(t_game *game_object); // delete me

/* Exit */
void	init_exit(t_game *game_object, int y, int x);
void	finish_game(void *param);

/* Handle Input */
void	handle_input(mlx_key_data_t keydata, void *param);
bool	is_movement(mlx_key_data_t keydata);
void	count_moves();

/* Utils */
void	assign_sprite_textures(t_animated_mob *mob);
void	assign_sprite_images(t_game *game_object, t_animated_mob *mob);

/* Handle errors */
void	cleanup_and_exit(t_game *game_object, t_exit_type exit_type, char *error_msg);

/* Free */
void	free_game_memory(t_game *game_object);
void	free_textures(mlx_texture_t **sprite_textures);
void	free_images(t_game *game_object, mlx_image_t **sprite_images);

#endif /* SO_LONG_H */