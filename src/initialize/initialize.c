/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:56:56 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/31 10:20:36 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void init_hooks(t_game *game_object);

void	init_game(t_game *game_object, char *map_name)
{
	// Allocate memory for map
	game_object->map = ft_calloc(sizeof(t_map), 1);
	if (!game_object->map)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for map.");
	
	// Check if map is valid
	check_map(game_object, map_name);

	game_object->mlx = mlx_init(game_object->map->width * TILE_PX, game_object->map->height * TILE_PX, "So Long", true);
	if (!game_object->mlx)
		cleanup_and_exit(game_object, FAIL, "Failed to initialize mlx.");
	
	// Initialize the map/draw it to window
	init_map(game_object);
	init_hooks(game_object);
}

static void init_hooks(t_game *game_object)
{
	mlx_loop_hook(game_object->mlx, &init_animation, game_object);
	mlx_loop_hook(game_object->mlx, &finish_game, game_object);
	mlx_key_hook(game_object->mlx, &handle_input, game_object);
}

