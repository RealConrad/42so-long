/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:21:48 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/28 16:32:53 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_map(t_game *game_object, char *map);

void	init_map(t_game *game_object, char *map_name)
{
	int		fd;
	int		y;
	char	*map_row_str;
	
	y = 0;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		cleanup_and_exit(FAIL, "Failed to open map file.");
	
	// Allocate memory for map plan
	game_object->map->map_plan = ft_calloc(MAX_LINES, sizeof(char *)); 
	if (!game_object->map->map_plan)
		cleanup_and_exit(FAIL, "Failed to allocate memory for map plan.");
	
	while ((map_row_str = get_next_line(fd))) // Get the map line by line
	{
		game_object->map->map_plan[y] = ft_strdup(map_row_str); // Make copy of map
		draw_map(game_object, map_row_str); // draw the map
		free(map_row_str); // free allocated memory from get_next_line()
		y++;
	}
	// Null terminate the 2D array
	game_object->map->map_plan[y] = NULL;
	close(fd);
}

static void	draw_map(t_game *game_object, char *map)
{
	int	i;
	int	x;
	static int y = 0;

	i = 0;
	x = 0;
	while(map[i] != '\n')
	{
		if (map[i] == '1')
			draw_tile(game_object, y * TILE_PX, x * TILE_PX, WALL_PATH);
		else if (map[i] == '0')
			draw_tile(game_object, y * TILE_PX, x * TILE_PX, GROUND_PATH);
		else if (map[i] == 'P')
		{
			draw_tile(game_object, y * TILE_PX, x * TILE_PX, GROUND_PATH);
			init_player(game_object, y * TILE_PX, x * TILE_PX);
		}
		else if (map[i] == 'C')
		{
			draw_tile(game_object, y * TILE_PX, x * TILE_PX, GROUND_PATH);
			init_collectable(game_object, y * TILE_PX, x * TILE_PX);
		}
		x++;
		i++;
	}
	y++;
}
