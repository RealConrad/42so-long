/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:21:48 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 18:59:57 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_map(t_game *game_object, char map_tile, int y, int x);

/**
 * @brief Initalizes the map. Loops through the entire map plan and
 * 		  draws each tile.
 * @param game_object The game object that holds the map data.
 */
void	init_map(t_game *game_object)
{
	int		x;
	int		y;

	y = 0;
	while (y < game_object->map->height)
	{
		x = 0;
		while (x < game_object->map->width)
		{
			draw_map(game_object, game_object->map->map_plan[y][x], y, x);
			x++;
		}
		y++;
	}
}

/**
 * @brief Draws each tile at the given y and x position
 * @param game_object The game object that holds game related data
 * @param map_tile The map tile to draw
 * @param y The y position to draw at
 * @param x The x position to draw at
 */
static void	draw_map(t_game *game_object, char map_tile, int y, int x)
{
	if (map_tile == WALL)
		draw_tile(game_object, y * TILE_PX, x * TILE_PX, WALL_PATH);
	else if (map_tile != WALL && map_tile != EXIT && map_tile != TRAP)
		draw_tile(game_object, y * TILE_PX, x * TILE_PX, GROUND_PATH);
	if (map_tile == PLAYER)
		init_player(game_object, y * TILE_PX, x * TILE_PX);
	else if (map_tile == COLLECTABLE)
		init_collectable(game_object, y * TILE_PX, x * TILE_PX);
	else if (map_tile == EXIT)
		init_exit(game_object, y * TILE_PX, x * TILE_PX);
	else if (map_tile == TRAP)
		init_trap(game_object, y * TILE_PX, x * TILE_PX);
	else if (map_tile == MIMIC)
		init_mimic(game_object, y * TILE_PX, x * TILE_PX);
	else if (map_tile == ENEMY)
		init_enemy(game_object, y * TILE_PX, x * TILE_PX);
}
