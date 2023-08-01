/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:02:57 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 11:20:38 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

static void	animate_collectables(t_collectables *collectable);
static void	animate_traps(t_game *game_object);

void	init_animation(void	*param)
{
	t_game			*game_object;
	static double	time = TIME_FOR_FRAME;

	game_object = (t_game *)param;
	time -= game_object->mlx->delta_time;
	if (time > 0)
		return;
	time = TIME_FOR_FRAME;
	animate_sprite(game_object->player);
	animate_collectables(game_object->map->collectables);
	if (game_object->map->num_traps >= 1)
		animate_traps(game_object);
}

static void	animate_collectables(t_collectables *collectable)
{
	bool			first_iteration;
	t_collectables	*temp;

	first_iteration = true;
	temp = collectable;
	// Loop through the entire linked list and animate each node
	while (first_iteration || temp != collectable)
	{
		// Only animate coins that haven't been collected yet
		if (!temp->is_collected)
			animate_sprite(temp->coin);
		first_iteration = false;
		temp = temp->next;
	}
}

static void	animate_traps(t_game *game_object)
{
	bool	first_iteration;
	t_trap	*temp;
	int		idle_time;
	int		active_time;
	
	idle_time = 20;
	active_time = 4;
	temp = game_object->map->traps;
	first_iteration = true;
	while (first_iteration || temp != game_object->map->traps)
	{
		temp->spike->animated_sprite[temp->spike->curr_frame]->enabled = false;
		if (temp->spike->curr_frame == 0)
		{
			temp->is_active = false;
			if (++(temp->spike->frame_skip_counter) >= idle_time)
			{
				temp->spike->frame_skip_counter = 0;
				temp->spike->curr_frame++;
				temp->forward = true;
			}
		}
		else
		{
			if (++(temp->spike->frame_skip_counter) >= active_time)
			{
				temp->is_active = true;
				temp->spike->frame_skip_counter = 0;
				if (temp->forward)
				{
					if (temp->spike->curr_frame >= 3)
					{
						temp->spike->curr_frame--;
						temp->forward = false;
					}
					else
						temp->spike->curr_frame++;
				}
				else
				{
					if (temp->spike->curr_frame <= 1)
						temp->spike->curr_frame--;
					else
						temp->spike->curr_frame--;
				}
			}
		}
		temp->spike->animated_sprite[temp->spike->curr_frame]->enabled = true;
		first_iteration = false;
		temp = temp->next;
	}
}
