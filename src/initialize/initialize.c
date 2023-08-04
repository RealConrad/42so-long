/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:56:56 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/04 11:45:53 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void init_hooks(t_game *game_object);

/**
 * @brief Initializes the game and mlx. The function also checks 
 * 		  if the map provided is valid. It also initializes mlx hooks.
 * @param game_object A pointer that holds the entire games data that will
 * 					  be initialized/set.
 * @param map_name The file path to the map provided.
 */
void	init_game(t_game *game_object, char *map_name)
{
	game_object->map = ft_calloc(sizeof(t_map), 1);
	if (!game_object->map)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for map.");
	
	check_map(game_object, map_name);
	
	game_object->hud = ft_calloc(sizeof(t_hud), 1);
	if (!game_object->hud)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for HUD.");

	game_object->mlx = mlx_init(game_object->map->width * TILE_PX, game_object->map->height * TILE_PX, "So Long", true);
	if (!game_object->mlx)
		cleanup_and_exit(game_object, FAIL, "Failed to initialize mlx.");
	
	init_map(game_object);
	init_hud(game_object);
	init_hooks(game_object);
}

/**
 * @brief Sets up all the necessary hooks for mlx that get called every frame
 * @param game_object The game_object which holds mlx and all game related data.
 */
static void init_hooks(t_game *game_object)
{
	mlx_loop_hook(game_object->mlx, &display_player_dialogue, game_object);
	mlx_loop_hook(game_object->mlx, &init_animation, game_object);
	mlx_key_hook(game_object->mlx, &handle_input, game_object);
	mlx_loop_hook(game_object->mlx, &check_if_player_should_die, game_object);
	mlx_loop_hook(game_object->mlx, &check_if_pickup_collectable, game_object);
	mlx_loop_hook(game_object->mlx, &display_player_move_count, game_object);
	mlx_loop_hook(game_object->mlx, &check_win_condition, game_object);
	if (game_object->enemy)
		mlx_loop_hook(game_object->mlx, &move_enemy, game_object);
}

