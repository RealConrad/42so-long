/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:12:40 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/29 18:06:01 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_collectable_object(t_animated_mob *collectable)
{
	collectable->sprite_path = ft_calloc(1, sizeof(char) * ft_strlen(COLLECTABLE_PATH) + 1);
	if (!collectable->sprite_path)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable sprite path.");

	collectable->sprites = ft_calloc(COLLECTABLE_SPRITE_COUNT, sizeof(mlx_texture_t *) * COLLECTABLE_SPRITE_COUNT + 1);
	if (!collectable->sprites)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable sprites.");
	collectable->animated_sprite = ft_calloc(COLLECTABLE_SPRITE_COUNT, sizeof(mlx_texture_t *) * COLLECTABLE_SPRITE_COUNT + 1);
	if (!collectable->sprites)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable sprites.");
}

void	assign_collectable_object(t_game *game_object, t_animated_mob *collectable, int y, int x)
{
	collectable->sprite_path = COLLECTABLE_PATH;
	collectable->num_sprites = COLLECTABLE_SPRITE_COUNT;
	collectable->width = COLLECTABLE_WIDTH_PX;
	collectable->height = COLLECTABLE_HEIGHT_PX;
	collectable->frame_skip_amount = 6;
	collectable->curr_frame = 0;
	collectable->frame_skip_counter = 0;
	collectable->x = x / TILE_PX;
	collectable->y = y / TILE_PX;
	assign_sprite_textures(collectable);
	assign_sprite_images(game_object, collectable);
}

void	add_collectable_node(t_game *game_object, t_collectables *new_collectable)
{
	t_collectables	*curr_collectable;

	new_collectable->next = NULL;
	new_collectable->prev = NULL;
	// If linked list has not been initialized yet
	if (!game_object->map->collectables)
	{
		game_object->map->collectables = new_collectable;
		new_collectable->next = new_collectable;
		new_collectable->prev = new_collectable;
	}
	else
	{
		curr_collectable = game_object->map->collectables;
		while (curr_collectable->next != game_object->map->collectables)
			curr_collectable = curr_collectable->next;
		curr_collectable->next = new_collectable;
		new_collectable->prev = curr_collectable;
		new_collectable->next = game_object->map->collectables;
		game_object->map->collectables->prev = new_collectable;
	}	
}
