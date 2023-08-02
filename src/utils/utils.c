/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:37:05 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/02 18:01:39 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

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
		return (NULL);
	// convert sprite_index to a string
	frame_number_str = ft_itoa(sprite_index);
	
	// Copy the sprite path to filename, ensuring the uninitialized memory from malloc is overwritten
	// Append the frame number and file extension to filename
	ft_strlcpy(filename, animation_config->sprite_path, FILENAME_SIZE);
	ft_strlcat(filename, frame_number_str, FILENAME_SIZE);
	ft_strlcat(filename, ".png", FILENAME_SIZE);
	
	// Free memory allocated by ft_itoa()
	free(frame_number_str);
	return (filename);
}

void	assign_sprite_textures(t_animated_mob *mob)
{
	char	*filename;
	int		i;

	i = 0;
	while (i < mob->num_sprites)
	{
		filename = get_sprites(i, mob);
		mob->sprites[i] = mlx_load_png(filename);
		if (filename)
			free(filename); // free memory allocated by get_sprites()
		i++;
	}
	mob->sprites[i] = NULL;
}

void	assign_sprite_images(t_game *game_object, t_animated_mob *mob)
{
	int	i;

	i = 0;
	while (i < mob->num_sprites)
	{
		mob->animated_sprite[i] = mlx_texture_to_image(game_object->mlx, mob->sprites[i]);
		mlx_resize_image(mob->animated_sprite[i], mob->width, mob->height);
		mob->animated_sprite[i]->enabled = false;
		mlx_image_to_window(game_object->mlx, mob->animated_sprite[i], mob->x * TILE_PX, mob->y * TILE_PX);
		i++;
	}
	mob->animated_sprite[i] = NULL;
}

void	assign_z_index(t_animated_mob *mob, int z_index)
{
	int	i;
	
	i = 0;
	while (mob->animated_sprite[i])
	{
		mlx_set_instance_depth(mob->animated_sprite[i]->instances, z_index);
		i++;
	}
}
