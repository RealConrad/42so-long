/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:08:25 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 17:05:43 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Initializes a new collectable at the given x and y coordinates
 * @param game_object The game object which will holds all game related data
 * @param y The y position (in PX) of the new collectable to be added
 * @param x The x position (in PX) of the new collectable to be added
 */
void	init_collectable(t_game *game_object, int y, int x)
{
	t_collectables	*new_collectable;

	new_collectable = ft_calloc(1, sizeof(t_collectables));
	if (!new_collectable)
		cleanup_and_exit(game_object, FAIL,
			"Failed to allocate memory for new collectable.");
	new_collectable->coin = ft_calloc(1, sizeof(t_animated_mob));
	if (!new_collectable->coin)
		cleanup_and_exit(game_object, FAIL,
			"Failed to allocate memory for collectable mob.");
	new_collectable->coin->num_sprites = COLLECTABLE_SPRITE_COUNT;
	if (allocate_mob_object(new_collectable->coin) == FAIL)
		cleanup_and_exit(game_object, FAIL,
			"Failed to allocate memory for collectable object.");
	assign_collectable_object(game_object, new_collectable->coin, y, x);
	add_collectable_node(game_object, new_collectable);
}

/**
 * @brief Checks if the player is standing on a collectable.
 * 		  If so, the collectable gets removed from the window.
 * @param param A void pointer that is type casted to `t_game`
 */
void	check_if_pickup_collectable(void *param)
{
	t_game	*game_object;

	game_object = (t_game *)param;
	if (game_object->hud->is_game_paused)
		return ;
	if (game_object->map->map_plan
		[game_object->player->y][game_object->player->x] == COLLECTABLE)
		remove_collectable(game_object);
}
