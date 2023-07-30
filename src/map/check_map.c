/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:50:51 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/30 14:35:05 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"
/*
	TODO:
		- Check if file has new line at end
		- Check if map is valid
*/

void	check_map(t_game *game_object, char *map_name)
{
	int		fd;
	int		i;
	char	*map_row_str;
	
	i = 0;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		cleanup_and_exit(game_object, FAIL, "Failed to open map file.");
	
	while ((map_row_str = get_next_line(fd)))
	{
		i = 0;
		while(map_row_str[i] != '\n')
		{
			if (map_row_str[i] == 'C')
				game_object->map->num_collectables += 1;
			i++;
		}
		free(map_row_str); // free allocated memory from get_next_line()
	}
	close(fd);
}
