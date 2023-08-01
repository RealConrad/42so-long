/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:45:09 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 10:54:30 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_if_player_should_die(void *param)
{
	t_game	*game_object;
	bool	first_iteration;
	t_trap	*temp;

	game_object = (t_game *)param;
	temp = game_object->map->traps;
	first_iteration = true;
	if (game_object->map->map_plan[game_object->player->y][game_object->player->x] == 'T')
	{
		while (first_iteration || temp != game_object->map->traps)
		{
			first_iteration = false;
			if (temp->spike->x == game_object->player->x && temp->spike->y == game_object->player->y && temp->is_active)
			{
				ft_printf("You died!\n");
				// cleanup_and_exit(game_object, SUCCESS, "");
			}
			temp = temp->next;
		}
	}
}
