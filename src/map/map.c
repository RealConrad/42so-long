/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:21:48 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/31 12:27:37 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_map(t_game *game_object, char map_tile, int y, int x);

void	init_map(t_game *game_object)
{
	int		x;
	int		y;
	
	y = 0;
	ft_printf("Map Height: %d :::: Width: %d\n", game_object->map->height, game_object->map->width);
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
	if (map_tile == '1')
		draw_tile(game_object, y * TILE_PX, x * TILE_PX, WALL_PATH);
	else if (map_tile != '1' && map_tile != 'E' && map_tile != 'T')
		draw_tile(game_object, y * TILE_PX, x * TILE_PX, GROUND_PATH);
	if (map_tile == 'P')
		init_player(game_object, y * TILE_PX, x * TILE_PX);
	else if (map_tile == 'C')
		init_collectable(game_object, y * TILE_PX, x * TILE_PX);
	else if (map_tile == 'E')
		init_exit(game_object, y * TILE_PX, x * TILE_PX);
	else if (map_tile == 'T')
		init_trap(game_object, y * TILE_PX, x * TILE_PX);
}
