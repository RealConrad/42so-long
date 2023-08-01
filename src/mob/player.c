/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:14:32 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 15:07:22 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_game *game_object, int y, int x)
{
	game_object->player = ft_calloc(sizeof(t_animated_mob), 1);
	if (!game_object->player)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for player.");

	game_object->player->num_sprites = PLAYER_SPRITE_COUNT;
	// Allocate memory for player struct
	if (allocate_mob_object(game_object->player) == FAIL)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for player object.");
	// Assign data to player struct
	assign_player_object(game_object, y, x);
	assign_z_index(game_object->player, 3);
}
