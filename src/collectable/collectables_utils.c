/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:12:40 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 11:10:52 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	allocate_collectable_object(t_animated_mob *collectable)
{
	// SOLVE: Don't need this....?
	// collectable->sprite_path = ft_calloc(1, sizeof(char) * ft_strlen(COLLECTABLE_PATH) + 1);
	// if (!collectable->sprite_path)
	// 	return (FAIL);

	collectable->sprites = ft_calloc(COLLECTABLE_SPRITE_COUNT, sizeof(mlx_texture_t *) * COLLECTABLE_SPRITE_COUNT + 1);
	if (!collectable->sprites)
		return (FAIL);

	collectable->animated_sprite = ft_calloc(COLLECTABLE_SPRITE_COUNT, sizeof(mlx_texture_t *) * COLLECTABLE_SPRITE_COUNT + 1);
	if (!collectable->sprites)
		return (FAIL);
	return (SUCCESS);
}

void	assign_collectable_object(t_game *game_object, t_animated_mob *collectable, int y, int x)
{
	collectable->sprite_path = COLLECTABLE_PATH;
	collectable->num_sprites = COLLECTABLE_SPRITE_COUNT;
	collectable->width = COLLECTABLE_WIDTH_PX;
	collectable->height = COLLECTABLE_HEIGHT_PX;
	collectable->frame_skip_amount = 1;
	collectable->frame_skip_counter = 0;
	collectable->curr_frame = 0;
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
	new_collectable->is_collected = false;
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

void	remove_collectable(t_game *game_object)
{
	t_collectables	*temp;
	bool			first_iteration;

	first_iteration = true;
	temp = game_object->map->collectables;
	while (first_iteration || temp != game_object->map->collectables)
	{
		first_iteration = false;
		if (!temp->is_collected && temp->coin->x == game_object->player->x && temp->coin->y == game_object->player->y)
		{
			temp->is_collected = true;
			temp->coin->animated_sprite[temp->coin->curr_frame]->enabled = false;
			game_object->map->num_collectables--;
			break ;
		}
		temp = temp->next;
	}
}
