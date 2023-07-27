/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:12:40 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/27 12:13:04 by cwenz            ###   ########.fr       */
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

void	assign_collectable_object(t_game *game_object, int collectable_index)
{
	int		i;
	char	*filename;

	i = 0;
	game_object->map->collectables[collectable_index]->sprite_path = COLLECTABLE_PATH;
	game_object->map->collectables[collectable_index]->num_sprites = COLLECTABLE_SPRITE_COUNT;
	game_object->map->collectables[collectable_index]->width = COLLECTABLE_WIDTH_PX;
	game_object->map->collectables[collectable_index]->height = COLLECTABLE_HEIGHT_PX;
	game_object->map->collectables[collectable_index]->frame_skip_amount = 2;
	game_object->map->collectables[collectable_index]->curr_frame = 0;
	game_object->map->collectables[collectable_index]->frame_skip_counter = 0;
	game_object->map->collectables[collectable_index]->blank_sprite = mlx_load_png(BLANK_SPRITE);
	game_object->map->collectables[collectable_index]->img = mlx_texture_to_image(game_object->mlx, game_object->map->collectables[collectable_index]->blank_sprite);
	while (i < COLLECTABLE_SPRITE_COUNT)
	{
		filename = get_sprites(i, game_object->map->collectables[collectable_index]);
		game_object->map->collectables[collectable_index]->sprites[i] = mlx_load_png(filename);
		free(filename); // free memory allocated by get_sprites()
		i++;
	}
}

void	remove_collectable(t_game *game_object)
{
	int	i;

	i = 0;
	while (i < game_object->map->num_collectables)
	{
		if (game_object->map->collectables[i]->x == game_object->player->x
			&& game_object->map->collectables[i]->y == game_object->player->y)
		{
			game_object->map->collectables[i]->x = 50 * TILE_PX;
			game_object->map->collectables[i]->y = 50 * TILE_PX;
			game_object->player->frame_skip_amount++;
			// mlx_delete_image(game_object->mlx, game_object->map->collectables[i]->img);
			mlx_delete_image(game_object->mlx, game_object->map->collectables[i]->animated_sprite);
			game_object->map->num_collectables--;
			break ;
		}
		i++;
	}
}

void	deallocate_collectable_object(t_game *game_object, int collectable_index)
{
	mlx_delete_image(game_object->mlx, game_object->map->collectables[collectable_index]->img);
	mlx_delete_image(game_object->mlx, game_object->map->collectables[collectable_index]->animated_sprite);
	free(game_object->map->collectables[collectable_index]);
}
