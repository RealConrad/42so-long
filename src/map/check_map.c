/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:50:51 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 16:36:09 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

static void	get_map_width(t_map *map, int line);
static void	read_map(t_game *game_object, int fd);
static void	check_map_surrounded_by_walls(t_game *game_object);

/**
 * @brief Checks to see if the given map is valid. If not it will clean up any 
 * 		  memory and exit out the program.
 * @param game_object
 * @param map_name The map file path.
 * @note The program will break if the map is taller than 250 lines.
 * 		 This is due memory allocation as I've hard-coded it.
 */
void	check_map(t_game *game_object, char *map_name)
{
	int		fd;
	
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		cleanup_and_exit(game_object, FAIL, "Failed to open map file, most likely invalid path.");
	check_map_name(game_object, map_name);

	// Allocate memory for map plan
	game_object->map->map_plan = ft_calloc(MAX_LINES, sizeof(char *)); 
	if (!game_object->map->map_plan)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for map plan.");

	read_map(game_object, fd);
	// Null terminate the 2D array
	game_object->map->map_plan[game_object->map->height + 1] = NULL;
	validate_map_items(game_object);
	check_map_width(game_object);
	check_map_surrounded_by_walls(game_object);
	close(fd);
}

static void	read_map(t_game *game_object, int fd)
{
	char	*map_row_str;
	int		y;

	y = 0;
	while ((map_row_str = get_next_line(fd)) != NULL)
	{
		// Make copy of map
		game_object->map->map_plan[y] = ft_strdup(map_row_str);
		if (y == 0)
			get_map_width(game_object->map, 0);
		count_map_row_items(game_object->map, y);
		free(map_row_str); // free allocated memory from get_next_line()
		if (game_object->map->map_plan[y][0] == '\n')
			cleanup_and_exit(game_object, FAIL, "The map has multiple new line character ('\\n') at the end of file.");
		y++;
	}
	game_object->map->height = y;
}

/**
 * @brief Gets the width of the map
 * @param map The map object that holds the map plan
 * @param line The line for which to calculate the width.
 * @note This function gets the width of map's specific line.
 */
static void	get_map_width(t_map *map, int line)
{
	int	x;

	x = 0;
	while (map->map_plan[line][x] != '\n')
		x++;
	map->width = x;
}

/**
 * @brief Checks if the map is surrounded by walls
 * @param game_object The game_object that holds the map plan.
 */
static void	check_map_surrounded_by_walls(t_game *game_object)
{
	int	i;

	i = 0;
	// Check bottom and top rows
	while(i < game_object->map->width)
	{
		if (game_object->map->map_plan[0][i] != WALL || game_object->map->map_plan[game_object->map->height - 1][i] != WALL)
			cleanup_and_exit(game_object, FAIL, "The map is not surrounded by walls on the bottom/top.");
		i++;
	}
	i = 0;
	// Check the first and last columns
	while (i < game_object->map->height)
	{
		if (game_object->map->map_plan[i][0] != WALL || game_object->map->map_plan[i][game_object->map->width - 1] != WALL)
			cleanup_and_exit(game_object, FAIL, "The map is not surrounded by walls on the left/right.");
		i++;
	}
}
