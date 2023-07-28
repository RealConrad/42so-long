/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:40:59 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/28 14:28:48 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Constructs and returns a string representing the
 * 		  file path of a player sprite based on the sprite index
 * @param sprite_index The index of the sprite to generate the file path for
 * @param animation_config A pointer to the t_animated_mob structure which 
 * 		  contains the base sprite path and other animation-related properties.
 * @return A pointer to a string that contains the file path.
 * 		   This should be freed by the caller when its no longer needed.
 */
char	*get_sprites(int sprite_index, t_animated_mob *animation_config)
{
	char	*filename;
	char	*frame_number_str;
	
	filename = ft_calloc(sizeof(char) * FILENAME_SIZE, 1);
	if (!filename)
		cleanup_and_exit(FAIL, "Failed to allocate memory for sprite file path.");
	// convert sprite_index to a string
	frame_number_str = ft_itoa(sprite_index);
	
	// Copy the sprite path to filename, ensuring the uninitialized memory from malloc is overwritten
	ft_strlcpy(filename, animation_config->sprite_path, FILENAME_SIZE);
	// Append the frame number and file extension to filename
	ft_strlcat(filename, frame_number_str, FILENAME_SIZE);
	ft_strlcat(filename, ".png", FILENAME_SIZE);
	
	// Free memory allocated by ft_itoa()
	free(frame_number_str);
	return (filename);
}

void	animate_sprite(t_game *game_object, t_animated_mob *animation_config)
{
	// If there's already a sprite, delete it to prevent displaying multiple hero sprites
	// if (animation_config->animated_sprite)
	// 	mlx_delete_image(game_object->mlx, animation_config->animated_sprite);

	// Only update the animation every frame_skip_amount frames to make it appear slower
	if (++(animation_config->frame_skip_counter) >= animation_config->frame_skip_amount)
	{
		animation_config->frame_skip_counter = 0; // reset counter
		// Cycle through player sprites
		animation_config->curr_frame = (animation_config->curr_frame + 1) % animation_config->num_sprites;
		// Set the player animation to the current sprite
		animation_config->animated_sprite = mlx_texture_to_image(game_object->mlx, animation_config->sprites[animation_config->curr_frame]);
	}
	else
		animation_config->animated_sprite = mlx_texture_to_image(game_object->mlx, animation_config->sprites[animation_config->curr_frame]);
	draw_animation_to_window(game_object, animation_config);
}

void	draw_animation_to_window(t_game *game_object, t_animated_mob *animation_config)
{
	int sprite_center_x;
	int sprite_center_y;

	// Update players position with the coordinates with the blank image we set earlier,
	// to move the animated sprite around. Convert to index values, not pixel values.
	animation_config->x = animation_config->img->instances[0].x / TILE_PX;
	animation_config->y = animation_config->img->instances[0].y / TILE_PX;

	// Calculate the pixel coordinates for the center of the sprite
	sprite_center_x = animation_config->x * TILE_PX + (TILE_PX / 2) - (animation_config->width / 2);
	sprite_center_y = animation_config->y * TILE_PX + (TILE_PX / 2) - (animation_config->height / 2);

	// Draw updated sprite to the window
	mlx_resize_image(animation_config->animated_sprite, animation_config->width, animation_config->height);
	mlx_image_to_window(game_object->mlx, animation_config->animated_sprite, sprite_center_x, sprite_center_y);
}
