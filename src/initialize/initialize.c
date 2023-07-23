/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:56:56 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/23 22:30:49 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void init_hooks(t_game *game_object);

void	init_game(t_game *game_object, char *map_name)
{
	game_object->mlx = mlx_init(WIDTH, HEIGHT, "Game", true);
	if (!game_object->mlx)
		cleanup_and_exit(EXIT_FAILURE, "Failed to initialize mlx.");
	init_map(game_object, map_name);
	init_hooks(game_object);
}

static void init_hooks(t_game *game_object)
{
	mlx_loop_hook(game_object->mlx, &init_animation, game_object);
	mlx_key_hook(game_object->mlx, &handle_input, game_object);
}

