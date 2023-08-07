/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:45:09 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 19:30:57 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	find_trap(t_game *game_object);
static void	find_mimic(t_game *game_object);

/**
 * @brief Checks if the player should die
 * @param param A void pointer that is type casted to (t_game *)
 */
void	check_if_player_should_die(void *param)
{
	t_game	*game_object;
	char	current_player_tile;

	game_object = (t_game *)param;
	if (game_object->hud->is_game_paused)
		return ;
	current_player_tile = game_object->map->map_plan
	[game_object->player->y][game_object->player->x];
	if (current_player_tile == TRAP)
		find_trap(game_object);
	else if (current_player_tile == MIMIC)
		find_mimic(game_object);
	else if (game_object->enemy
		&& game_object->player->x == game_object->enemy->x
		&& game_object->player->y == game_object->enemy->y)
	{
		game_object->hud->is_player_dead = true;
		end_game(game_object, DIED);
	}
}

/**
 * @brief Checks if the player is standing on a trap
 * @param game_object Holds all game related data, including player + trap
 */
static void	find_trap(t_game *game_object)
{
	bool	first_iteration;
	t_trap	*temp;

	first_iteration = true;
	temp = game_object->map->traps;
	while (first_iteration || temp != game_object->map->traps)
	{
		first_iteration = false;
		if (temp->spike->x == game_object->player->x
			&& temp->spike->y == game_object->player->y
			&& temp->is_active)
		{
			game_object->hud->is_player_dead = true;
			end_game(game_object, DIED);
		}
		temp = temp->next;
	}
}

/**
 * @brief Checks if the player is standing on a mimic
 * @param game_object Holds all game related data, including player + mimics
 */
static void	find_mimic(t_game *game_object)
{
	bool	first_iteration;
	t_mimic	*temp;

	first_iteration = true;
	temp = game_object->map->mimics;
	while (first_iteration || temp != game_object->map->mimics)
	{
		first_iteration = false;
		if (temp->chest->x == game_object->player->x
			&& temp->chest->y == game_object->player->y)
		{
			game_object->hud->is_player_dead = true;
			end_game(game_object, DIED);
		}
		temp = temp->next;
	}
}
