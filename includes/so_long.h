/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:57:51 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/11 18:38:45 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <stdlib.h>

/* Include libraries */
# include "../libraries/42c-library/c_library.h" 
# include "../libraries/MLX42/include/MLX42/MLX42.h"


# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define WIDTH 1000
# define HEIGHT 1000

# define MOVE_SPEED 50

typedef struct s_player {
	mlx_texture_t	*sprite;
	mlx_image_t		*img;
	int				curr_frame;
} t_player;

typedef struct s_game {
	mlx_t			*mlx;
	t_player		*player;
}	t_game;

/* Initialize */
void	init_game(t_game *game_object);

/* Handle Input */
void	handle_input(mlx_key_data_t keydata, void *param);
bool	is_movement(mlx_key_data_t keydata);
void	count_moves();

/* Handle errors */
void	cleanup_and_exit();

#endif /* SO_LONG_H */