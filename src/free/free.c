/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:28:22 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 15:22:21 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

static void	free_collectables(t_game *game_object);
static void	free_player(t_game *game_object);
static void free_map(t_game *game_object);

/**
 * @brief Frees the entire game object.
 * @param game_object The game object to be freed.
 */
void	free_game_memory(t_game *game_object)
{
	if (game_object)
	{
		if (game_object->map && game_object->map->collectables)
			free_collectables(game_object);
		if (game_object->map && game_object->map->mimics)
			free_mimics(game_object);
		if (game_object->map && game_object->map->traps)
			free_traps(game_object);
		if (game_object->hud)
			free_hud(game_object);
		if (game_object->map)
			free_map(game_object);
		if (game_object->player)
			free_player(game_object);
		if (game_object->enemy)
			free_enemy(game_object);
		if (game_object->mlx)
		{
			mlx_terminate(game_object->mlx);
			mlx_close_window(game_object->mlx);
		}
		free(game_object);
	}
}

/**
 * @brief Loops through the linked list of collectables and frees
 * 		  each collectable.
 * @param game_object The game object that holds the collectables.
 */
static void	free_collectables(t_game *game_object)
{
	t_collectables	*temp;
	t_collectables	*curr_temp;

	temp = game_object->map->collectables;
	temp->prev->next = NULL;
	while(temp->next)
	{
		free_textures(temp->coin->sprites);
		free_images(game_object, temp->coin->animated_sprite);
		free(temp->coin);
		// Make copy of current node and free current node
		curr_temp = temp;
		temp = temp->next;
		free(curr_temp);
	}
	// Free last node
	free_textures(temp->coin->sprites);
	free_images(game_object, temp->coin->animated_sprite);
	free(temp->coin);
	free(temp);
}

/**
 * @brief Frees the memory allocated for the player.
 * @param game_object The game object that holds the player.
 */
static void	free_player(t_game *game_object)
{
	free_textures(game_object->player->sprites);
	free_images(game_object, game_object->player->animated_sprite);
	free(game_object->player);
}

/**
 * @brief Frees the map.
 * @param game_object The game object that holds the map.
 */
static void free_map(t_game *game_object)
{
	int	y;

	y = 0;
	if (game_object->map->map_plan)
	{
		while(game_object->map->map_plan[y])
		{
			free(game_object->map->map_plan[y]);
			game_object->map->map_plan[y] = NULL;
			y++;
		}
		free(game_object->map->map_plan);
		game_object->map->map_plan = NULL;
	}
	free(game_object->map);
	game_object->map = NULL;
}
