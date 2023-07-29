/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:37:05 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/29 17:56:07 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	assign_sprite_textures(t_animated_mob *mob)
{
	char	*filename;
	int		i;

	i = 0;
	while (i < mob->num_sprites)
	{
		filename = get_sprites(i, mob);
		mob->sprites[i] = mlx_load_png(filename);
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
