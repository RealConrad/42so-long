/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:01:47 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/02 12:24:10 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

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

void	free_hud(t_game *game_object)
{
	(void)game_object;
}
