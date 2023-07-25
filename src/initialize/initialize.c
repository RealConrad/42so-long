/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:56:56 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/25 14:19:59 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void init_hooks(t_game *game_object);

void	init_game(t_game *game_object, char *map_name)
{
	game_object->mlx = mlx_init(WIDTH, HEIGHT, "Game", true);
	if (!game_object->mlx)
		cleanup_and_exit(FAIL, "Failed to initialize mlx.");
	// Allocate memory for map
	game_object->map = ft_calloc(sizeof(t_map), 1);
	if (!game_object->map)
		cleanup_and_exit(FAIL, "Failed to allocate for map.");
		
	check_map(game_object, map_name);
	init_map(game_object, map_name);
	ft_printf("Collectables: %d\n", game_object->map->num_collectables);
	init_hooks(game_object);
}

static void init_hooks(t_game *game_object)
{
	mlx_loop_hook(game_object->mlx, &init_animation, game_object);
	mlx_key_hook(game_object->mlx, &handle_input, game_object);
}

