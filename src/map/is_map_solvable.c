/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_solvable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:14:32 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/04 14:44:21 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_map_position	find_position(t_game *game_object, char tile);
static bool				is_move_valid(t_game *game_object, int y, int x,
							int has_visited[MAX_LINES][MAX_LINES]);
static void				flood_fill(t_game *game_object, int y, int x,
							int has_visited[MAX_LINES][MAX_LINES]);

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
				cleanup_and_exit(game_object, FAIL, "Map is not solvable!");
			x++;
		}
		y++;
	}
}

static void	flood_fill(t_game *game_object, int y, int x, int has_visited[MAX_LINES][MAX_LINES])
{
	int	i;
	int	direction_x[] = { -1, 0, 0, 1};
	int	direction_y[] = { 0, -1, 1, 0};
	int	new_x;
	int	new_y;

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

static bool	is_move_valid(t_game *game_object, int y, int x, int has_visited[MAX_LINES][MAX_LINES])
{
	if (game_object->map->map_plan[y][x] == WALL || has_visited[y][x])
		return (false);
	return (true);
}