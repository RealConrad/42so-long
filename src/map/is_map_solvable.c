/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_solvable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:14:32 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/06 14:26:54 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_map_position	find_position(t_game *game_object, char tile);
static bool				is_move_valid(t_game *game_object, int y, int x,
							int has_visited[MAX_LINES][MAX_LINES]);
static void				flood_fill(t_game *game_object, int y, int x,
							int has_visited[MAX_LINES][MAX_LINES]);

/**
 * @brief Checks if the map is solvable
 * @param game_object The gameo bject that contains the map
 */
void	check_map_solvable(t_game *game_object)
{
	t_map_position	player_pos;
	int				has_visited[MAX_LINES][MAX_LINES];
	int				x;
	int				y;
	
	y = 0;
	player_pos = find_position(game_object, PLAYER);
	flood_fill(game_object, player_pos.y, player_pos.x, has_visited);

	while (y < game_object->map->height)
	{
		x = 0;
		while (x < game_object->map->width)
		{
			if ((game_object->map->map_plan[y][x] == COLLECTABLE || game_object->map->map_plan[y][x] == EXIT) 
				&& !has_visited[y][x])
				cleanup_and_exit(game_object, FAIL, "Map is not solvable.");
			x++;
		}
		y++;
	}
}

/**
 * @brief Implementation of the algorithm flood fill
 * @param game_object The game object that contains the map
 * @param y The current y position
 * @param x The current x position
 * @param has_visited An array that contains data if the tile (y,x) has been visited
 */
static void	flood_fill(t_game *game_object, int y, int x, int has_visited[MAX_LINES][MAX_LINES])
{
	int					i;
	static int			direction_x[] = {-1, 0, 0, 1};
	static int			direction_y[] = {0, -1, 1, 0};
	int					new_x;
	int					new_y;

	i = 0;
	has_visited[y][x] = 1; // Mark current tile as visited;
	
	// Check all four directions (top, left, right, bottom)
	while (i < 4)
	{
		new_x = x + direction_x[i];
		new_y = y + direction_y[i];
		if (is_move_valid(game_object, new_y, new_x, has_visited))
			flood_fill(game_object, new_y, new_x, has_visited);
		i++;
	}
}

/**
 * @brief Finds the position of a given tile
 * @param game_object The game object that holdst the map plan
 * @param tile The tile to find
 * @return The position of the tile found, else returns the position
 * 		   of (0,0).
 */
static t_map_position	find_position(t_game *game_object, char tile)
{
	t_map_position	pos;

	pos.y = 0;
	while (game_object->map->map_plan[pos.y])
	{
		pos.x = 0;
		while (game_object->map->map_plan[pos.y][pos.x])
		{
			if (game_object->map->map_plan[pos.y][pos.x] == tile)
				return (pos);
			pos.x++;
		}
		pos.y++;
	}
	return (pos);
}

/**
 * @brief Checks if the given tile at the x and y is valid
 * @param game_object The game object that holds the map plan
 * @param y The y position in the map plan
 * @param x The x position in the map plan
 * @param has_visited An array that contains if the tile has been visited already or not
 * @return Returns true if the tile is valid, else false
 */
static bool	is_move_valid(t_game *game_object, int y, int x, int has_visited[MAX_LINES][MAX_LINES])
{
	if (game_object->map->map_plan[y][x] == WALL || has_visited[y][x])
		return (false);
	return (true);
}