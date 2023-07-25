/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:12:40 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/25 13:32:44 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_collectable_object(t_animated_mob *collectable)
{
	collectable->sprite_path = ft_calloc(sizeof(char) * ft_strlen(COLLECTABLE_PATH) + 1, 1);
	if (!collectable->sprite_path)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable sprite path.");

	collectable->sprites = ft_calloc(sizeof(mlx_texture_t *) * COLLECTABLE_SPRITE_COUNT, 1);
	if (!collectable->sprites)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable sprites.");
}
void	assign_collectable_object(t_game *game_object)
{
	int		i;
	char	*filename;

	i = 0;
	game_object->map->collectables->sprite_path = COLLECTABLE_PATH;
	game_object->map->collectables->num_sprites = COLLECTABLE_SPRITE_COUNT;
	game_object->map->collectables->width = COLLECTABLE_WIDTH_PX;
	game_object->map->collectables->height = COLLECTABLE_HEIGHT_PX;
	game_object->map->collectables->frame_skip_amount = 8;
	game_object->map->collectables->curr_frame = 0;
	game_object->map->collectables->frame_skip_counter = 0;
	game_object->map->collectables->blank_sprite = mlx_load_png(BLANK_SPRITE);
	game_object->map->collectables->img = mlx_texture_to_image(game_object->mlx, game_object->map->collectables->blank_sprite);
	while (i < COLLECTABLE_SPRITE_COUNT)
	{
		filename = get_sprites(i, game_object->map->collectables);
		game_object->map->collectables->sprites[i] = mlx_load_png(filename);
		free(filename); // free memory allocated by get_sprites()
		i++;
	}
}
