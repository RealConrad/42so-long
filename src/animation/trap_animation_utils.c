/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trap_animation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:35:36 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/03 16:49:02 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	animate_trap_idle(t_trap *trap, int idle_time)
{
	trap->is_active = false;
	if (++(trap->spike->frame_skip_counter) >= idle_time)
	{
		trap->spike->frame_skip_counter = 0;
		trap->spike->curr_frame++;
		trap->forward = true;
	}
}

void	animate_trap_active(t_trap *trap, int active_time)
{
	if (++(trap->spike->frame_skip_counter) >= active_time)
	{
		trap->is_active = true;
		trap->spike->frame_skip_counter = 0;
		if (trap->forward)
		{
			if (trap->spike->curr_frame >= 3)
			{
				trap->spike->curr_frame--;
				trap->forward = false;
			}
			else
				trap->spike->curr_frame++;
		}
		else
		{
			if (trap->spike->curr_frame <= 1)
				trap->spike->curr_frame--;
			else
				trap->spike->curr_frame--;
		}
	}
}

void	update_mimic_sprite(t_game *game_object)
{
	t_mimic	*temp;
	bool	first_iteration;

	temp = game_object->map->mimics;
	first_iteration = true;
	while (first_iteration || temp != game_object->map->mimics)
	{
		if (temp->chest->y == game_object->player->y && temp->chest->x == game_object->player->x)
		{
			temp->chest->animated_sprite[0]->enabled = false;
			temp->chest->animated_sprite[1]->instances->x = temp->chest->x * TILE_PX + (TILE_PX / 2) - (temp->chest->width / 2);
			temp->chest->animated_sprite[1]->instances->y = temp->chest->y * TILE_PX + (TILE_PX / 2) - (temp->chest->height / 2);
			temp->chest->animated_sprite[1]->enabled = true;
			return ;	
		}
		first_iteration = false;
		temp = temp->next;
	}
}
