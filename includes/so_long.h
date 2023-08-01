/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:57:51 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 15:04:08 by cwenz            ###   ########.fr       */
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
# define PLAYER_SPRITE_COUNT 4
# define PLAYER_HEIGHT_PX 64
# define PLAYER_WIDTH_PX 36

/* Mimic */
# define MIMIC_SPRITE_PATH "./assets/enemy/mimic/idle"
# define MIMIC_SPRITE_COUNT 3
# define MIMIC_HEIGHT_PX 50
# define MIMIC_WIDTH_PX 36

/* Map */
# define WALL_PATH "./assets/world/map/wall.png"
# define GROUND_PATH "./assets/world/map/floor.png"
# define GROUND_PATH_2 "./assets/world/map/floor2.png"
# define EXIT_PATH "./assets/world/exit/exit.png"
# define TILE_PX 64
# define MAX_LINES 250

/* Collectables */
# define COLLECTABLE_PATH "./assets/world/collectables/coin"
# define COLLECTABLE_SPRITE_COUNT 4
# define COLLECTABLE_HEIGHT_PX 24
# define COLLECTABLE_WIDTH_PX 16

/* Traps */
# define TRAP_PATH "./assets/world/trap/trap"
# define TRAP_SPRITE_COUNT 4
# define TRAP_HEIGHT_PX 64
# define TRAP_WIDTH_PX 64

typedef enum e_exit_type {
	SUCCESS,
	FAIL,
}	t_exit_type;

typedef enum e_tile_type {
	WALL,
	GROUND,
}	t_tile_type;

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

typedef struct s_trap {
	t_animated_mob	*spike;
	bool			is_active;
	bool			forward;
	struct s_trap	*next;
	struct s_trap	*prev;
}	t_trap;

typedef struct s_mimic {
	t_animated_mob	*chest;
	struct s_mimic	*next;
	struct s_mimic	*prev;
}	t_mimic;

typedef struct s_map {
	char			**map_plan;
	mlx_image_t		*exit;
	mlx_image_t		*map_img;
	t_collectables	*collectables;
	t_mimic			*mimics;
	t_trap			*traps;
	int				num_collectables;
	int				num_exits;
	int				num_players;
	int				num_enemies;
	int				num_traps;
	int				num_mimics;
	int				height;
	int				width;
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
void	check_if_player_should_die(void *param);

/* Collectables */
void	init_collectable(t_game *game_object, int y, int x);
bool	allocate_collectable_object(t_animated_mob *collectable);
void	assign_collectable_object(t_game *game_object, t_animated_mob *collectable, int y, int x);
void	add_collectable_node(t_game *game_object, t_collectables *new_collectable);
void	check_if_pickup_collectable(void *param);
void	remove_collectable(t_game *game_object);

/* Animation */
void	init_animation(void	*param);
char	*get_sprites(int	sprite_index, t_animated_mob *animation_config);
void	animate_sprite(t_animated_mob *animation_config);
void	update_sprite_position(t_animated_mob *animation_config);
void	animate_trap_idle(t_trap *trap, int idle_time);
void	animate_trap_active(t_trap *trap, int active_time);

/* Map */
void	init_map(t_game *game_object);
void	draw_tile(t_game *game_object, int y, int x, char *path);
void	check_map(t_game *game_object, char *map_name);
void	check_map_name(t_game *game_object, char *map_name);
void	check_map_width(t_game *game_object);
void	count_map_row_items(t_map *map, int y);
void	validate_map_items(t_game *game_object);

/* Trap */
void	init_trap(t_game *game_object, int y, int x);
bool	allocate_trap_object(t_animated_mob *spike);
void	assign_trap_object(t_game *game_object, t_animated_mob *spike, int y, int x);
void	add_spike_node(t_game *game_object, t_trap *trap);

/* Mimic */
void	init_mimic(t_game *game_object, int y, int x);

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
void	assign_z_index(t_animated_mob *mob, int z_index);
bool	allocate_mob_object(t_animated_mob *mob);

/* Handle errors */
void	cleanup_and_exit(t_game *game_object, t_exit_type exit_type, char *error_msg);

/* Free */
void	free_game_memory(t_game *game_object);
void	free_textures(mlx_texture_t **sprite_textures);
void	free_images(t_game *game_object, mlx_image_t **sprite_images);

#endif /* SO_LONG_H */
