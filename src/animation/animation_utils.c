/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:40:59 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/30 13:56:13 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Animates a given sprite by looping through images every `animation_config->frame_skip_counter`.
 * 		  Also updates the sprites position.
 * @param animation_config The sprite to animate.
 */
void	animate_sprite(t_animated_mob *animation_config)
{
	animation_config->animated_sprite[animation_config->curr_frame]->enabled = false;
	if (++(animation_config->frame_skip_counter) >= animation_config->frame_skip_amount)
	{
		animation_config->frame_skip_counter = 0; // reset counter
		animation_config->curr_frame = (animation_config->curr_frame + 1) % animation_config->num_sprites;
	}
	animation_config->animated_sprite[animation_config->curr_frame]->enabled = true;
	update_sprite_position(animation_config);
}

/**
 * @brief Updates the sprits position and ensures its centered on the map tile.
 * @param animation_config The sprites whose position is updated.
 */
void	update_sprite_position(t_animated_mob *animation_config)
{
	int sprite_center_x;
	int sprite_center_y;

	// Calculate the pixel coordinates for the center of the sprite
	sprite_center_x = animation_config->x * TILE_PX + (TILE_PX / 2) - (animation_config->width / 2);
	sprite_center_y = animation_config->y * TILE_PX + (TILE_PX / 2) - (animation_config->height / 2);

	animation_config->animated_sprite[animation_config->curr_frame]->instances->x = sprite_center_x;
	animation_config->animated_sprite[animation_config->curr_frame]->instances->y = sprite_center_y;
}
