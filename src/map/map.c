/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:21:48 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 16:34:10 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
1 = Wall
0 = Floor
P = Player
C = Collectable
E = Exit
T = Trap
M = Mimic
D = Demon
*/
static void	draw_map(t_game *game_object, char map_tile, int y, int x);

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
