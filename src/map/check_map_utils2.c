/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:58:25 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 19:10:40 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_valid_tile(char tile);

/**
 * @brief Checks to see if the map contains any invalid characters
 * 		  that are not recorganized.
 * @param game_object The game object that holds the map data,
 * @param y The row of the map to check for,
 */
void	check_map_chars(t_game *game_object, int y)
{
	int	x;

	x = 0;
	while (game_object->map->map_plan[y][x] != '\n'
		&& game_object->map->map_plan[y][x] != '\0')
	{
		if (!is_valid_tile(game_object->map->map_plan[y][x]))
			cleanup_and_exit(game_object, FAIL,
				"Map has invalid tiles.");
		x++;
	}
}

/**
 * @brief checks if the given tile is valid.
 * @param tile The tile to check for.
 * @return Returns true if the tile is valid or
 * 		   false if invalid.
 */
static bool	is_valid_tile(char tile)
{
	if (tile == WALL || tile == GROUND || tile == ENEMY
		|| tile == PLAYER || tile == MIMIC || tile == COLLECTABLE
		|| tile == EXIT || tile == TRAP)
		return (true);
	return (false);
}
