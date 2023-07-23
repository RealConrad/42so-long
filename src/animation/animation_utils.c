/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:40:59 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/23 21:56:19 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Constructs and returns a string representing the
 * 		  file path of a player sprite based on the sprite index
 * @param sprite_index The index of the sprite to generate the file path for
 * @param animation_config
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
