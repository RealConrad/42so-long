/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:43:59 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 15:00:06 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

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
void	count_map_row_items(t_map *map, int y)
{
	int	x;

	x = 0;
	while(map->map_plan[y][x] && map->map_plan[y][x] != '\n')
	{
		if (map->map_plan[y][x] == 'C')
			map->num_collectables++;
		else if (map->map_plan[y][x] == 'P')
			map->num_players++;
		else if (map->map_plan[y][x] == 'E')
			map->num_exits++;
		else if (map->map_plan[y][x] == 'P')
			map->num_enemies++;
		else if (map->map_plan[y][x] == 'T')
			map->num_traps++;
		else if (map->map_plan[y][x] == 'M')
			map->num_mimics++;
		x++;
	}
}

void	validate_map_items(t_game *game_object)
{
	if (game_object->map->num_players != 1)
		cleanup_and_exit(game_object, FAIL, "The map must contain 1 player.");
	else if (game_object->map->num_exits != 1)
		cleanup_and_exit(game_object, FAIL, "The map must contain 1 exit.");
	else if (game_object->map->num_collectables < 1)
		cleanup_and_exit(game_object, FAIL, "The map must contain at least 1 collectable.");
}

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
