/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:34:22 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 18:57:13 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_movement(t_game *game_object);

/**
 * @brief Checks for specific key strokes (WASD for movement), and
 * 		  ESC for quitting the game and handles each appropriately
 * @param keydata Contains information about the key that was pressed.
 * @param param A void poiner that gets typecasted to (t_game *).
 */
void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game_object;

	game_object = (t_game *)param;
	if (is_movement(keydata)
		&& (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT)
		&& !game_object->hud->is_game_paused)
		handle_movement(game_object);
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_ESCAPE))
		cleanup_and_exit(game_object, SUCCESS, "");
}

/**
 * @brief Updatest the players position based on the key pressed (WASD)
 * @param game_object The game_object that holds the player object.
 */
static void	handle_movement(t_game *game_object)
{
	int	delta_x;
	int	delta_y;

	delta_x = 0;
	delta_y = 0;
	if (mlx_is_key_down(game_object->mlx, MLX_KEY_W))
		delta_y = UP;
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_S))
		delta_y = DOWN;
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_A))
		delta_x = LEFT;
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_D))
		delta_x = RIGHT;
	if (game_object->map->map_plan[game_object->player->y
			+ delta_y][game_object->player->x + delta_x] != WALL)
	{
		game_object->player->x += delta_x;
		game_object->player->y += delta_y;
		game_object->hud->has_player_moved = true;
		game_object->hud->num_player_moves++;
	}
}
