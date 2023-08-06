/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:01:47 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/06 16:44:07 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

/**
 * @brief Loops through an array of textures and frees them.
 * @param sprite_textures The array of textures that will be freed.
 */
void	free_textures(mlx_texture_t **sprite_textures)
{
	int	i;

	i = 0;
	while (sprite_textures[i])
	{
		mlx_delete_texture(sprite_textures[i]);
		i++;
	}
	free(sprite_textures);
}

/**
 * @brief Loops through an array of images and frees them
 * @param game_object The game object that holds all game related data,
 * 		  including the images.
 * @param sprite_images The array of images that will be freed.
 */
void	free_images(t_game *game_object, mlx_image_t **sprite_images)
{
	int	i;

	i = 0;
	while (sprite_images[i])
	{
		mlx_delete_image(game_object->mlx, sprite_images[i]);
		i++;
	}
	free(sprite_images);
}

/**
 * @brief Frees the memory allocated for the hud
 * @param game_object The game object that holds all game related data,
 * 		  including the hud.
 */
void	free_hud(t_game *game_object)
{
	if (game_object->hud->dialogue_img)
	{
		free_textures(game_object->hud->dialogue_img->sprites);
		free_images(game_object, game_object->hud->dialogue_img->animated_sprite);
		free(game_object->hud->dialogue_img);
	}
	free(game_object->hud);
}
