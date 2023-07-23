/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:15:12 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/23 17:39:29 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_animation_to_window(t_game *game_object);

/**
 * @brief Constructs and returns a string representing the
 * 		  file path of a player sprite based on the sprite index
 * @param sprite_index The index of the sprite to generate the file path for
 * @return A pointer to a string that contains the file path.
 * 		   This should be freed by the caller when its no longer needed.
 */
char	*get_player_sprites(int	sprite_index)
{
	char	*filename;
	char	*frame_number_str;
	
	filename = ft_calloc(sizeof(char) * FILENAME_SIZE, 1);
	if (!filename)
		cleanup_and_exit(FAIL, "Failed to allocate memory for player sprite file path.");
	// convert sprite_index to a string
	frame_number_str = ft_itoa(sprite_index);
	
	// Copy the sprite path to filename, ensuring the uninitialized memory from malloc is overwritten
	ft_strlcpy(filename, PLAYER_SPRITE_PATH, FILENAME_SIZE);
	// Append the frame number and file extension to filename
	ft_strlcat(filename, frame_number_str, FILENAME_SIZE);
	ft_strlcat(filename, ".png", FILENAME_SIZE);
	
	// Free memory allocated by ft_itoa()
	free(frame_number_str);
	return (filename);
}

/**
 * @brief Function to loop through and animate players idle animation.
 * 
 * The function gets called each frame.
 * It cycles through each player sprite in the sequence by updating the curr_fram
 * index and sets the players animation to the new sprite.
 * 
 * It then updates the players position with the coordinates of current 
 * image instance (which is a blank image) and draws it to the screen.
 * 
 * @param param A void pointer that should point to the t_game struct
 * 
 * @note This function relies on an "invisible" blank sprite that travels around the map.
 *		 The role of this blank sprite is to act as a placeholder for the player's position.
 *		 The animation of the visible sprite is essentially "following" the blank sprite's position.
 *		 In every animation frame, the function updates the position of the blank sprite and
 *		 applies the corresponding animation to the visible sprite at that position. This ensures
 * 		 smooth animation as the player moves around the game map. Without the blank sprite it would
 * 		 segfault.
 */
void	loop_player_idle_animation(void *param)
{
	t_game 		*game_object;
	static int	frame_skip_counter = 0;
	static bool	first_loop = true;
	int			frame_skip_amount;

	frame_skip_amount = 8;
	game_object = (t_game *)param;
	// If there's already a sprite, delete it to prevent displaying multiple hero sprites
	if (game_object->player->animation)
		mlx_delete_image(game_object->mlx, game_object->player->animation);
	// Only update the animation every 10 frames to make it appear slower
	if (!first_loop && ++frame_skip_counter >= frame_skip_amount)
	{
		frame_skip_counter = 0; // reset counter
		// Cycle through player sprites
		game_object->player->curr_frame = (game_object->player->curr_frame + 1) % PLAYER_SPRITE_COUNT;
		// Set the player animation to the current sprite
		game_object->player->animation = mlx_texture_to_image(game_object->mlx, game_object->player->sprites[game_object->player->curr_frame]);
	}
	else
	{
		first_loop = false;
		game_object->player->animation = mlx_texture_to_image(game_object->mlx, game_object->player->sprites[game_object->player->curr_frame]);	
	}
	draw_animation_to_window(game_object);
}

/**
 * @brief Draws the player's animated sprite to the window at the calculated pixel coordinates to center the sprite on a tile.
 * The sprite's position is updated based on the blank image's coordinates, which are then converted from pixel values to index values.
 * The function calculates the pixel coordinates for the center of the sprite, considering the dimensions of the sprite and the tile size.
 * Then the sprite image is resized and drawn to the window at the calculated center coordinates.
 *
 * @param game_object A pointer to the game object structure which contains the player object and its properties including its sprite and position.
 */
static void	draw_animation_to_window(t_game *game_object)
{
	int sprite_center_x;
	int sprite_center_y;

	// Update players position with the coordinates with the blank image we set earlier,
	// to move the animated sprite around. Convert to index values, not pixel values.
	game_object->player->x = game_object->player->img->instances[0].x / TILE_PX;
	game_object->player->y = game_object->player->img->instances[0].y / TILE_PX;

	// Calculate the pixel coordinates for the center of the sprite
	// I use + 20 for the height to better center the player in each tile, as the player
	// dimenstions are different compared to the tiles dimenstions 
	sprite_center_x = game_object->player->x * TILE_PX + (TILE_PX / 2) - (PLAYER_WIDTH_PX / 2);
	sprite_center_y = game_object->player->y * TILE_PX + (TILE_PX / 2) - ((PLAYER_HEIGHT_PX + 20) / 2);

	// Draw updated sprite to the window
	mlx_resize_image(game_object->player->animation, PLAYER_WIDTH_PX, PLAYER_HEIGHT_PX);
	mlx_image_to_window(game_object->mlx, game_object->player->animation, sprite_center_x, sprite_center_y);
}
