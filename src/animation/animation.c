/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:02:57 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/23 22:34:54 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

static void	draw_animation_to_window(t_game *game_object, t_animated_mob *animation_config);
static void	animate_sprite(t_game *game_object, t_animated_mob *animation_config);

void	init_animation(void	*param)
{
	t_game	*game_object;
	
	game_object = (t_game *)param;
	
	// Animate player
	animate_sprite(game_object, game_object->player);

}

static void	animate_sprite(t_game *game_object, t_animated_mob *animation_config)
{
	static int	frame_skip_counter = 0;
	static bool	first_loop = true;

	// If there's already a sprite, delete it to prevent displaying multiple hero sprites
	if (animation_config->animated_sprite)
		mlx_delete_image(game_object->mlx, animation_config->animated_sprite);
	// Only update the animation every 10 frames to make it appear slower
	if (!first_loop && ++frame_skip_counter >= animation_config->frame_skip_amount)
	{
		frame_skip_counter = 0; // reset counter
		// Cycle through player sprites
		animation_config->curr_frame = (animation_config->curr_frame + 1) % animation_config->num_sprites;
		// Set the player animation to the current sprite
		animation_config->animated_sprite = mlx_texture_to_image(game_object->mlx, animation_config->sprites[animation_config->curr_frame]);
	}
	else
	{
		first_loop = false;
		animation_config->animated_sprite = mlx_texture_to_image(game_object->mlx, animation_config->sprites[animation_config->curr_frame]);	
	}
	draw_animation_to_window(game_object, animation_config);
}


static void	draw_animation_to_window(t_game *game_object, t_animated_mob *animation_config)
{
	int sprite_center_x;
	int sprite_center_y;

	// Update players position with the coordinates with the blank image we set earlier,
	// to move the animated sprite around. Convert to index values, not pixel values.
	animation_config->x = animation_config->img->instances[0].x / TILE_PX;
	animation_config->y = animation_config->img->instances[0].y / TILE_PX;

	// Calculate the pixel coordinates for the center of the sprite
	sprite_center_x = animation_config->x * TILE_PX + (TILE_PX / 2) - (animation_config->width / 2);
	sprite_center_y = animation_config->y * TILE_PX + (TILE_PX / 2) - ((animation_config->height + 20) / 2);

	// Draw updated sprite to the window
	mlx_resize_image(animation_config->animated_sprite, animation_config->width, animation_config->height);
	mlx_image_to_window(game_object->mlx, animation_config->animated_sprite, sprite_center_x, sprite_center_y);
}
