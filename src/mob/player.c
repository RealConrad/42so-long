/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:14:32 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/29 16:25:55 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_game *game_object, int y, int x)
{
	// int sprite_center_x;
	// int sprite_center_y;

	game_object->player = ft_calloc(sizeof(t_animated_mob), 1);
	if (!game_object->player)
		cleanup_and_exit(FAIL, "Failed to allocate memory for player.");

	// Allocate memory for player struct
	allocate_player_object(game_object->player);
	// Assign data to player struct
	assign_player_object(game_object, y, x);
	
	// Make the player centered in the tile
	// sprite_center_x = game_object->player->x * TILE_PX + (TILE_PX / 2) - (game_object->player->width / 2);
	// sprite_center_y = game_object->player->y * TILE_PX + (TILE_PX / 2) - (game_object->player->height / 2);
}
