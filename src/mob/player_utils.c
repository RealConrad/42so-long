/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:15:12 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/30 15:22:17 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	allocate_player_object(t_animated_mob *player)
{
	// SOLVE: Dont need this....?
	// player->sprite_path = ft_calloc(1, sizeof(char) * ft_strlen(PLAYER_SPRITE_PATH) + 1);
	// if (!player->sprite_path)
	// 	return (FAIL);

	player->sprites = ft_calloc(PLAYER_SPRITE_COUNT, sizeof(mlx_texture_t *) * PLAYER_SPRITE_COUNT + 1);
	if (!player->sprites)
		return (FAIL);
		
	player->animated_sprite = ft_calloc(PLAYER_SPRITE_COUNT, sizeof(mlx_image_t *) * PLAYER_SPRITE_COUNT + 1);
	if (!player->animated_sprite)
		return (FAIL);
	return (SUCCESS);
}

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
}
