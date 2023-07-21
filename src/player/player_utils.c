/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:15:12 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/21 15:24:21 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	
	filename = malloc(sizeof(char) * FILENAME_SIZE);
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

	// only update the animation every 10 frames to make it appear slower
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
	// Update players position with the coordinates with the blank image we set earlier,
	// to move the animated sprite around.
	game_object->player->x = game_object->player->img->instances->x;
	game_object->player->y = game_object->player->img->instances->y;
	
	// Draw updated sprite to the window
	mlx_resize_image(game_object->player->animation, PLAYER_WIDTH_PX, PLAYER_HEIGHT_PX);
	mlx_image_to_window(game_object->mlx, game_object->player->animation, game_object->player->x, game_object->player->y);
}
