/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:57:51 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/13 20:11:53 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stdlib.h>

/* Include libraries */
# include "../libraries/42c-library/c_library.h" 
# include "../libraries/MLX42/include/MLX42/MLX42.h"

/* Player */
# define PLAYER_SPRITE_PATH "./assets/player/HeroKnight_Idle_"
# define MAX_SPRITES 7
# define MOVE_SPEED 50

# define FILENAME_SIZE 50

/* Game dimensions */
# define WIDTH 1000
# define HEIGHT 1000

typedef enum e_exit_type {
	SUCCESS,
	FAIL,
}	t_exit_type;

typedef struct s_player {
	mlx_texture_t	**sprites; // Array of sprites, one for each frame
	mlx_image_t		*img; // current image
	int				curr_frame; // index of the current frame
} t_player;

typedef struct s_game {
	mlx_t			*mlx;
	t_player		*player;
}	t_game;

/* Initialize */
void	init_game(t_game *game_object);
char	*get_player_sprites(int	sprite_index);

/* Player */
void	loop_player_idle_animation(void *param);

/* Handle Input */
void	handle_input(mlx_key_data_t keydata, void *param);
bool	is_movement(mlx_key_data_t keydata);
void	count_moves();

/* Handle errors */
void	cleanup_and_exit();

#endif /* SO_LONG_H */