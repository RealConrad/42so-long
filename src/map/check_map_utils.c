/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:43:59 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/06 13:44:56 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

/**
 * @brief Checks if the given map name is valid.
 * @param game_object The game object that holds all game related data.
 * @param map_name The map name that is to be checked.
 */
void	check_map_name(t_game *game_object, char *map_name)
{
	int		i;
	int		j;
	char	*file_type;

	i = ft_strlen(map_name) - 4;
	j = 0;
	file_type = ".ber";
	while (map_name[i])
	{
		if (map_name[i] != file_type[j])
			cleanup_and_exit(game_object, FAIL, "Map is not a .ber file.");
		i++;
		j++;
	}
}
/**
 * @brief Counts the number of map elemnts there are.
 * @param map The map to count the number of elements.
 * @param y The y-axis of the map to check for.
 */
void	count_map_row_items(t_map *map, int y)
{
	int	x;

	x = 0;
	while(map->map_plan[y][x] && map->map_plan[y][x] != '\n')
	{
		if (map->map_plan[y][x] == COLLECTABLE)
			map->num_collectables++;
		else if (map->map_plan[y][x] == PLAYER)
			map->num_players++;
		else if (map->map_plan[y][x] == EXIT)
			map->num_exits++;
		else if (map->map_plan[y][x] == TRAP)
			map->num_traps++;
		else if (map->map_plan[y][x] == MIMIC)
			map->num_mimics++;
		else if (map->map_plan[y][x] == ENEMY)
			map->num_enemies++;
		x++;
	}
}

/**
 * @brief Checks to see if the map has the correct number of map elements.
 * @param game_object The game object which holds the map data.
 */
void	validate_map_items(t_game *game_object)
{
	if (game_object->map->num_players != 1)
		cleanup_and_exit(game_object, FAIL, "The map must contain 1 player.");
	else if (game_object->map->num_exits != 1)
		cleanup_and_exit(game_object, FAIL, "The map must contain 1 exit.");
	else if (game_object->map->num_collectables < 1)
		cleanup_and_exit(game_object, FAIL, "The map must contain at least 1 collectable.");
	else if (game_object->map->num_enemies > 1)
		cleanup_and_exit(game_object, FAIL, "The game can only have 1 enemy.");
}

/**
 * @brief Checks to see if the map has a consistent width.
 * @param game_object The game object that holds the map data.
 */
void	check_map_width(t_game *game_object)
{
	int	y;
	int	x;

	y = 0;
	while (y < game_object->map->height)
	{
		x = 0;
		while (game_object->map->map_plan[y][x] != '\n' && game_object->map->map_plan[y][x] != '\0')
			x++;
		if (x != game_object->map->width)
			cleanup_and_exit(game_object, FAIL, "The map has an inconsistent width.");
		y++;		
	}
}
