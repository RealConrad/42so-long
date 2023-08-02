/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:34:22 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/02 13:20:44 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_movement(t_game *game_object);

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game_object;

	game_object = (t_game *)param;
	if (is_movement(keydata)
		&& (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		handle_movement(game_object);
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_ESCAPE))
		display_game_over(game_object);
}

static void	handle_movement(t_game *game_object)
{
	int tile_x;
	int	tile_y;
	int delta_x = 0;
	int	delta_y = 0;

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

	if (game_object->map->map_plan[tile_y][tile_x] != WALL)
	{
		game_object->player->x = tile_x;
		game_object->player->y = tile_y;
		game_object->hud->has_player_moved = true;
		game_object->hud->num_player_moves++;
	}
}
