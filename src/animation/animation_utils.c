/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:40:59 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 16:57:23 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Animates a given mob by looping through images every 
 * 		  `anim_config->frame_skip_counter`.
 * 		  Also updates the sprites position.
 * @param anim_config The mob to animate.
 */
void	animate_sprite(t_animated_mob *anim_config)
{
	anim_config->animated_sprite[anim_config->curr_frame]->enabled = false;
	if (++(anim_config->frame_skip_counter) >= anim_config->frame_skip_amount)
	{
		anim_config->frame_skip_counter = 0; // reset counter
		anim_config->curr_frame = (anim_config->curr_frame + 1)
			% anim_config->num_sprites;
	}
	anim_config->animated_sprite[anim_config->curr_frame]->enabled = true;
	update_sprite_position(anim_config);
}

/**
 * @brief Updates a mob's position and ensures its centered on the map tile.
 * @param anim_config The mob whose position is updated.
 */
void	update_sprite_position(t_animated_mob *anim_config)
{
	int	sprite_center_x;
	int	sprite_center_y;

	// Calculate the pixel coordinates for the center of the sprite
	sprite_center_x = anim_config->x * TILE_PX + (TILE_PX / 2)
		- (anim_config->width / 2);
	sprite_center_y = anim_config->y * TILE_PX + (TILE_PX / 2)
		- ((anim_config->height + anim_config->offset_image_px) / 2);
	anim_config->animated_sprite[anim_config->curr_frame]->instances->x
		= sprite_center_x;
	anim_config->animated_sprite[anim_config->curr_frame]->instances->y
		= sprite_center_y;
}
