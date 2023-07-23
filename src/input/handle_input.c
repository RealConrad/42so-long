/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:34:22 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/23 17:12:46 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_movement(t_game *game_object);

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game_object;

	game_object = (t_game *)param;
	if (is_movement(keydata))
		handle_movement(game_object);
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game_object->mlx);
}

static void	handle_movement(t_game *game_object)
{
	int tile_x, tile_y;
	int delta_x = 0, delta_y = 0;

	if (mlx_is_key_down(game_object->mlx, MLX_KEY_W))
		delta_y = -1;
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_S))
		delta_y = 1;
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_A))
		delta_x = -1;
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_D))
		delta_x = 1;
	
	tile_x = game_object->player->x + delta_x;
	tile_y = game_object->player->y + delta_y;
	
	if (game_object->map->map_plan[tile_y][tile_x] != '1')
	{
		game_object->player->x = tile_x;
		game_object->player->y = tile_y;
	}
	// Update the actual position of the player's sprite
	game_object->player->img->instances[0].x = game_object->player->x * TILE_PX + (TILE_PX / 2) - (PLAYER_WIDTH_PX / 2);
	game_object->player->img->instances[0].y = game_object->player->y * TILE_PX + (TILE_PX / 2) - (PLAYER_HEIGHT_PX / 2);
}
