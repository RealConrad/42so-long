/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:02:57 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/02 17:46:46 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

static void	animate_collectables(t_collectables *collectable);
static void	animate_traps(t_game *game_object);
static void	animate_mimics(t_mimic *mimic);

void	init_animation(void	*param)
{
	t_game			*game_object;
	static double	time = TIME_FOR_FRAME;

	game_object = (t_game *)param;
	time -= game_object->mlx->delta_time;
	if (time > 0)
		return;
	time = TIME_FOR_FRAME;
	if (game_object->hud->is_game_paused)
	{
		if (game_object->enemy)
			update_sprite_position(game_object->enemy);
		update_sprite_position(game_object->player);
		return ;
	}
	animate_sprite(game_object->player);
	animate_collectables(game_object->map->collectables);
	if (game_object->map->num_mimics >= 1)
		animate_mimics(game_object->map->mimics);
	if (game_object->map->num_traps >= 1)
		animate_traps(game_object);
	if (game_object->enemy)
		animate_sprite(game_object->enemy);
}

static void	animate_collectables(t_collectables *collectable)
{
	bool			first_iteration;
	t_collectables	*temp;

	first_iteration = true;
	temp = collectable;
	while (first_iteration || temp != collectable)
	{
		// Only animate coins that haven't been collected yet
		if (!temp->is_collected)
			animate_sprite(temp->coin);
		first_iteration = false;
		temp = temp->next;
	}
}

static void	animate_mimics(t_mimic *mimic)
{
	bool			first_iteration;
	t_mimic			*temp;

	first_iteration = true;
	temp = mimic;
	while (first_iteration || temp != mimic)
	{
		animate_sprite(temp->chest);
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
	
	idle_time = 10;
	active_time = 4;
	temp = game_object->map->traps;
	first_iteration = true;
	while (first_iteration || temp != game_object->map->traps)
	{
		temp->spike->animated_sprite[temp->spike->curr_frame]->enabled = false;
		if (temp->spike->curr_frame == 0)
			animate_trap_idle(temp, idle_time);
		else
			animate_trap_active(temp, active_time);
		temp->spike->animated_sprite[temp->spike->curr_frame]->enabled = true;
		first_iteration = false;
		temp = temp->next;
	}
}
