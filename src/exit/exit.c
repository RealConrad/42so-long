/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:53:18 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 17:08:30 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Initalizes the exit for the player to be able to
 * 		  complete the level.
 * @param game_object The game object which holds all game
 * 		  related data, including the exit.
 * @param y The y-position (in PX) of the exit.
 * @param x The x-position (in PX) of the exit.
 */
void	init_exit(t_game *game_object, int y, int x)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(EXIT_PATH);
	if (!texture)
		cleanup_and_exit(game_object, FAIL,
			"Failed to load closed door texture.");
	game_object->map->exit = mlx_texture_to_image(game_object->mlx, texture);
	game_object->map->exit->enabled = true;
	// Delete texture, no longer needed.
	mlx_delete_texture(texture);
	mlx_resize_image(game_object->map->exit, TILE_PX, TILE_PX);
	mlx_image_to_window(game_object->mlx, game_object->map->exit, x, y);
	mlx_set_instance_depth(game_object->map->exit->instances, 1);
}

/**
 * @brief Checks to see if the player has beat the game.
 * @param param A void pointe that gets type casted to (t_game *).
 */
void	check_win_condition(void *param)
{
	t_game		*game_object;
	static bool	is_completed = true;

	if (!is_completed)
		return ;
	game_object = (t_game *)param;
	if (game_object->map->num_collectables == 0
		&& (game_object->map->exit->instances->x / TILE_PX)
		== game_object->player->x
		&& (game_object->map->exit->instances->y / TILE_PX)
		== game_object->player->y)
	{
		is_completed = false;
		end_game(game_object, COMPLETED);
	}
}
