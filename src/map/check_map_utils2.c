/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:58:25 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/04 14:15:56 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool				is_valid_tile(char tile);

void	check_map_chars(t_game *game_object, int y)
{
	int	x;

	x = 0;
	while(game_object->map->map_plan[y][x] != '\n' && game_object->map->map_plan[y][x] != '\0')
	{
		if (!is_valid_tile(game_object->map->map_plan[y][x]))
			cleanup_and_exit(game_object, FAIL, "Map has invalid tiles.");
		x++;
	}

}

static bool	is_valid_tile(char tile)
{
	if (tile == WALL || tile == GROUND || tile == ENEMY 
		|| tile == PLAYER || tile == MIMIC || tile == COLLECTABLE
		|| tile == EXIT || tile == TRAP)
		return (true);
	return (false);
}