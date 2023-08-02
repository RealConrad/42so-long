/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:45:09 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/02 12:38:04 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	is_standing_on_trap(t_game *game_object);
static void	is_standing_on_mimic(t_game *game_object);
static void	is_player_touching_enemy(t_game *game_object);

void	check_if_player_should_die(void *param)
{
	t_game	*game_object;
	char	current_player_tile;

	game_object = (t_game *)param;
	current_player_tile = game_object->map->map_plan[game_object->player->y][game_object->player->x];
	if (current_player_tile == TRAP)
		is_standing_on_trap(game_object);
	else if (current_player_tile == MIMIC)
		is_standing_on_mimic(game_object);
	else if (game_object->enemy
		&& game_object->player->x == game_object->enemy->x
		&& game_object->player->y == game_object->enemy->y)
		is_player_touching_enemy(game_object);
}

static void	is_standing_on_trap(t_game *game_object)
{
	bool	first_iteration;
	t_trap	*temp;

	first_iteration = true;
	temp = game_object->map->traps;
	while (first_iteration || temp != game_object->map->traps)
	{
		first_iteration = false;
		if (temp->spike->x == game_object->player->x && temp->spike->y == game_object->player->y && temp->is_active)
		{
			ft_printf("You died!\n");
			game_object->hud->is_player_dead = true;
		}
		temp = temp->next;
	}
}

static void	is_standing_on_mimic(t_game *game_object)
{
	bool	first_iteration;
	t_mimic	*temp;

	first_iteration = true;
	temp = game_object->map->mimics;
	while (first_iteration || temp != game_object->map->mimics)
	{
		first_iteration = false;
		if (temp->chest->x == game_object->player->x && temp->chest->y == game_object->player->y)
		{
			ft_printf("You died!\n");
			game_object->hud->is_player_dead = true;
		}
		temp = temp->next;
	}
}

static void	is_player_touching_enemy(t_game *game_object)
{
	(void)game_object;
	ft_printf("You died!\n");
	game_object->hud->is_player_dead = true;
}
