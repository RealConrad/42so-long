/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:58:00 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/06 13:18:00 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

/**
 * @brief Frees the memory allocated for the enemy.
 * @param game_object The game object that holds all game related data,
 * 		  including the enemy.
 */
void	free_enemy(t_game *game_object)
{
	free_textures(game_object->enemy->sprites);
	free_images(game_object, game_object->enemy->animated_sprite);
	free(game_object->enemy);
}

/**
 * @brief Frees the memory allocated for all traps;
 * @param game_object The game object that holds all game related data,
 * 		  including the traps.
 */
void	free_traps(t_game *game_object)
{
	bool	first_iteration;
	t_trap	*temp;

	temp = game_object->map->traps;
	first_iteration = true;
	while (first_iteration || temp != game_object->map->traps)
	{
		first_iteration = false;
		free_textures(temp->spike->sprites);
		free_images(game_object, temp->spike->animated_sprite);
		free(temp->spike);
		temp = temp->next;
	}
	free(temp);
}

/**
 * @brief Frees the memory allocated for all the mimics
 * @param game_object The game object that holds all game related data,
 * 		  including the mimics.
 */
void	free_mimics(t_game *game_object)
{
	bool	first_iteration;
	t_mimic	*temp;

	first_iteration = true;
	temp = game_object->map->mimics;
	while (first_iteration || temp != game_object->map->mimics)
	{
		first_iteration = false;
		free_textures(temp->chest->sprites);
		free_images(game_object, temp->chest->animated_sprite);
		free(temp->chest);
		temp = temp->next;
	}
	free(temp);
}
