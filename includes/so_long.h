/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:57:51 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/27 13:20:06 by cwenz            ###   ########.fr       */
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

/* Player */
# define PLAYER_SPRITE_PATH "./assets/player/idle"
# define BLANK_SPRITE "./assets/player/blank.png"
# define PLAYER_SPRITE_COUNT 4
# define PLAYER_HEIGHT_PX 64
# define PLAYER_WIDTH_PX 36

/* Map */
# define WALL_PATH "./assets/world/wall.png"
# define GROUND_PATH "./assets/world/floor.png"
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
	mlx_image_t		*animated_sprite; // The animation image
	mlx_texture_t	*blank_sprite; // Used for animation to work
	mlx_image_t		*img;
	char			*sprite_path; // file path to sprites
	int				frame_skip_counter;
	int				frame_skip_amount; // Used for speed of animation
	int				curr_frame; // index of the current frame
	int				num_sprites;
	int				height;
	int				width;
	int				x; // x index of sprite
	int				y; // y index of sprite
}	t_animated_mob;

typedef struct s_collectables {
	t_animated_mob			*mob;
	struct s_collectables	*next;
}	t_collectables;

typedef struct s_map {
	char			**map_plan;
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
void	assign_player_object(t_game *game_object);
void	allocate_player_object(t_animated_mob *player);

/* Collectables */
void	init_collectable(t_game *game_object, int y, int x);
void	allocate_collectable_object(t_animated_mob *collectable);
void	assign_collectable_object(t_game *game_object, t_animated_mob *collectable);

/* Animation */
void	init_animation(void	*param);
char	*get_sprites(int	sprite_index, t_animated_mob *animation_config);
void	animate_sprite(t_game *game_object, t_animated_mob *animation_config);
void	draw_animation_to_window(t_game *game_object, t_animated_mob *animation_config);
void	animate_sprite2(t_game *game_object, t_animated_mob *animation_config);
void	draw_animation_to_window2(t_game *game_object, t_animated_mob *animation_config);

/* Map */
void	init_map(t_game *game_object, char *map_name);
void	draw_tile(t_game *game_object, int y, int x, char *path);
void	check_map(t_game *game_object, char *map_name);
void	print_map(t_game *game_object); // delete me

/* Handle Input */
void	handle_input(mlx_key_data_t keydata, void *param);
bool	is_movement(mlx_key_data_t keydata);
void	remove_collectable(t_game *game_object);
void	deallocate_collectable_object(t_game *game_object, int collectable_index);
void	count_moves();

/* Handle errors */
void	cleanup_and_exit(t_exit_type exit_type, char *error_msg);

#endif /* SO_LONG_H */