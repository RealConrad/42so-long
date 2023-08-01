/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:44:28 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 16:53:22 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	assign_enemy_object(t_game *game_object, int y, int x);

void	init_enemy(t_game *game_object, int y, int x)
{
	game_object->enemy = ft_calloc(1, sizeof(t_animated_mob));
	if (!game_object->enemy)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for enemy.");
	
	game_object->enemy->num_sprites = ENEMY_SPRITE_COUNT;
	// Allocate memory for enemy
	if (allocate_mob_object(game_object->enemy) == FAIL)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for enemy object.");
	assign_enemy_object(game_object, y, x);
}

static void	assign_enemy_object(t_game *game_object, int y, int x)
{
	game_object->enemy->sprite_path = ENEMY_SPRITE_PATH;
	game_object->enemy->width = ENEMY_WIDTH_PX;
	game_object->enemy->height = ENEMY_HEIGHT_PX;
	game_object->enemy->frame_skip_amount = 0;
	game_object->enemy->frame_skip_counter = 0;
	game_object->enemy->offset_image_px = 15;
	game_object->enemy->curr_frame = 0;
	game_object->enemy->x = x / TILE_PX;
	game_object->enemy->y = y / TILE_PX;
	assign_sprite_textures(game_object->enemy);
	assign_sprite_images(game_object, game_object->enemy);
	assign_z_index(game_object->enemy, 4);
}
