/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:56:56 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/14 17:55:10 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void update_game_state(t_game *game_object);

void	init_game(t_game *game_object, char *map_name)
{
	game_object->mlx = mlx_init(WIDTH, HEIGHT, "Game", true);

	init_map(game_object, map_name);
	init_player(game_object);
	if (!game_object->mlx || !game_object->player)
		cleanup_and_exit(FAIL);

	update_game_state(game_object);
}

static void update_game_state(t_game *game_object)
{
	mlx_loop_hook(game_object->mlx, &loop_player_idle_animation, game_object);
	mlx_key_hook(game_object->mlx, &handle_input, game_object);
}

