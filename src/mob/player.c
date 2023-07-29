/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:14:32 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/29 17:51:02 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_game *game_object, int y, int x)
{
	game_object->player = ft_calloc(sizeof(t_animated_mob), 1);
	if (!game_object->player)
		cleanup_and_exit(FAIL, "Failed to allocate memory for player.");

	// Allocate memory for player struct
	allocate_player_object(game_object->player);
	// Assign data to player struct
	assign_player_object(game_object, y, x);
}
