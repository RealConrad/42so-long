/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 14:28:22 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 17:06:18 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

static void	free_collectables(t_game *game_object);
static void	free_player(t_game *game_object);
static void free_map(t_game *game_object);

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

static void	free_collectables(t_game *game_object)
{
	t_collectables	*temp;
	bool			first_iteration;

	temp = game_object->map->collectables;
	first_iteration = true;
	while(first_iteration || temp != game_object->map->collectables)
	{
		first_iteration = false;
		free_textures(temp->coin->sprites);
		free_images(game_object, temp->coin->animated_sprite);
		free(temp->coin);
		temp = temp->next;
	}
	free(temp);
}

static void	free_player(t_game *game_object)
{
	free_textures(game_object->player->sprites);
	free_images(game_object, game_object->player->animated_sprite);
	free(game_object->player);
}

static void free_map(t_game *game_object)
{
	int	y;

	y = 0;
	if (game_object->map->map_plan)
	{
		while(game_object->map->map_plan[y])
		{
			free(game_object->map->map_plan[y]);
			y++;
		}
		free(game_object->map->map_plan);
	}
	free(game_object->map);
}
