/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:14:32 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/06 15:14:28 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	assign_player_object(t_game *game_object, int y, int x);

/**
 * @brief Initializes and creates the player at x and y position
 * @param game_object Holds all game related data
 * @param y The y position (in PX) of the player
 * @param x The x position (in PX) of the player
 */
void	init_player(t_game *game_object, int y, int x)
{
	game_object->player = ft_calloc(sizeof(t_animated_mob), 1);
	if (!game_object->player)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for player.");

	game_object->player->num_sprites = PLAYER_SPRITE_COUNT;
	// Allocate memory for player
	if (allocate_mob_object(game_object->player) == FAIL)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for player object.");
	// Assign data to player struct
	assign_player_object(game_object, y, x);
}

/**
 * @brief Assigns data to the player object
 * @param game_object Holds all game related data
 * @param y The y position (in PX) of the player
 * @param x The x position (in PX) of the player
 */
static void	assign_player_object(t_game *game_object, int y, int x)
{
	game_object->player->sprite_path = PLAYER_SPRITE_PATH;
	game_object->player->width = PLAYER_WIDTH_PX;
	game_object->player->height = PLAYER_HEIGHT_PX;
	game_object->player->frame_skip_amount = 0;
	game_object->player->frame_skip_counter = 0;
	game_object->player->offset_image_px = 20;
	game_object->player->curr_frame = 0;
	game_object->player->x = x / TILE_PX;
	game_object->player->y = y / TILE_PX;
	game_object->hud->is_player_dead = false;
	assign_sprite_textures(game_object->player);
	assign_sprite_images(game_object, game_object->player);
	assign_z_index(game_object->player, 3);
}
