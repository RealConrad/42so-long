/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:08:25 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/29 17:37:35 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	init_collectable(t_game *game_object, int y, int x)
{
	t_collectables	*new_collectable;
	t_collectables	*curr_collectable;
	int 			sprite_center_x;
	int 			sprite_center_y;

	new_collectable = ft_calloc(1, sizeof(t_collectables));
	if (!new_collectable)
		cleanup_and_exit(FAIL, "Failed to allocate memory for new collectable.");
	new_collectable->mob = ft_calloc(1, sizeof(t_animated_mob));
	if (!new_collectable->mob)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable mob.");

	// Allocate memory for collectable struct
	allocate_collectable_object(new_collectable->mob);
	// Assign values for collectables
	assign_collectable_object(game_object, new_collectable->mob, y, x);
	
	// Make the player centered in the tile
	sprite_center_x = new_collectable->mob->x * TILE_PX + (TILE_PX / 2) - (new_collectable->mob->width / 2);
	sprite_center_y = new_collectable->mob->y * TILE_PX + (TILE_PX / 2) - (new_collectable->mob->height / 2);

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
