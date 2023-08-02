/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:52:36 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/02 10:10:48 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

/**
 * @brief Assigns data for a trap object.
 * @param game_object The game object used to initialize the images of the trap
 * @param spike The trap
 * @param y The y-axis position of the trap represented in PX
 * @param x The x-axis position of the trap represented in PX
 */
void	assign_trap_object(t_game *game_object, t_animated_mob *spike, int y, int x)
{
	spike->sprite_path = TRAP_PATH;
	spike->width = TRAP_WIDTH_PX;
	spike->height = TRAP_HEIGHT_PX;
	spike->frame_skip_amount = 0;
	spike->frame_skip_counter = 0;
	spike->curr_frame = 0;
	spike->offset_image_px = 0;
	spike->x = x / TILE_PX;
	spike->y = y / TILE_PX;
	assign_sprite_textures(spike);
	assign_sprite_images(game_object, spike);
	assign_z_index(spike, 1);
}

/**
 * @brief Adds a given trap to the end of the linked list
 * @param game_object The game object that holds the linked list
 * @param new_spike The new trap that will be added to the linked list
 */
void	add_spike_node(t_game *game_object, t_trap *new_spike)
{
	t_trap	*curr_spike;

	new_spike->next = NULL;
	new_spike->prev = NULL;
	new_spike->is_active = false;
	new_spike->forward = true;
	// If linked list has not been initialized yet
	if (!game_object->map->traps)
	{
		game_object->map->traps = new_spike;
		new_spike->next = new_spike;
		new_spike->prev = new_spike;	
	}
	else
	{
		curr_spike = game_object->map->traps;
		while (curr_spike->next != game_object->map->traps)
			curr_spike = curr_spike->next;
		curr_spike->next = new_spike;
		new_spike->prev = curr_spike;
		new_spike->next = game_object->map->traps;
		game_object->map->traps->prev = new_spike;
	}
}
