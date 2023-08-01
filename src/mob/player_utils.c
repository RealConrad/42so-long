/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:15:12 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 14:32:24 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	assign_player_object(t_game *game_object, int y, int x)
{
	game_object->player->sprite_path = PLAYER_SPRITE_PATH;
	game_object->player->num_sprites = PLAYER_SPRITE_COUNT;
	game_object->player->width = PLAYER_WIDTH_PX;
	game_object->player->height = PLAYER_HEIGHT_PX;
	game_object->player->frame_skip_amount = 0;
	game_object->player->frame_skip_counter = 0;
	game_object->player->curr_frame = 0;
	game_object->player->x = x / TILE_PX;
	game_object->player->y = y / TILE_PX;
	assign_sprite_textures(game_object->player);
	assign_sprite_images(game_object, game_object->player);
	assign_z_index(game_object->player, 2);
}
