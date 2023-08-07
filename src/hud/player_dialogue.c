/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_dialogue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:19:06 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 18:52:35 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	display_dialogue(t_game *game_object);
static void	hide_dialogues(t_game *game_object);
static void	hide_active_dialogue(t_game *game_object);

/**
 * @brief Displays random player dialogue.
 * @param param A void pointer that is typecasted to (t_game *).
 */
void	display_player_dialogue(void *param)
{
	t_game	*game_object;
	int		rand_num;

	game_object = (t_game *)param;
	if (game_object->hud->is_game_paused)
		return ;
	rand_num = (rand() % 5);
	if (!game_object->hud->is_dialogue_displayed
		&& ++game_object->hud->dialogue_img->frame_skip_counter
		>= game_object->hud->dialogue_img->frame_skip_amount)
	{
		game_object->hud->dialogue_img->frame_skip_counter = 0;
		game_object->hud->is_dialogue_displayed = true;
		game_object->hud->dialogue_img->curr_frame = rand_num;
		display_dialogue(game_object);
	}
	else if (game_object->hud->is_dialogue_displayed)
		hide_active_dialogue(game_object);
}

/**
 * @brief Hides all dialogues and displays a new dialogue.
 * @param game_object The game object that holds all game related data,
 * 		  including the dialogue image.
 */
static void	display_dialogue(t_game *game_object)
{
	hide_dialogues(game_object);
	game_object->hud->dialogue_img->animated_sprite
	[game_object->hud->dialogue_img->curr_frame]->enabled = true;
	game_object->hud->dialogue_img->animated_sprite
	[game_object->hud->dialogue_img->curr_frame]->instances->x
		= (game_object->player->x * TILE_PX) + 20;
	game_object->hud->dialogue_img->animated_sprite
	[game_object->hud->dialogue_img->curr_frame]->instances->y
		= (game_object->player->y * TILE_PX) - 50;
}

/**
 * @brief Hides the active dialogue every active_amount frames (local variable).
 * @param game_object The game object that holds all game related data.
 */
static void	hide_active_dialogue(t_game *game_object)
{
	static int	active_timer = 0;
	int			active_amount;

	active_amount = 200;
	game_object->hud->dialogue_img->animated_sprite
	[game_object->hud->dialogue_img->curr_frame]->instances->x
		= (game_object->player->x * TILE_PX) + 20;
	game_object->hud->dialogue_img->animated_sprite
	[game_object->hud->dialogue_img->curr_frame]->instances->y
		= (game_object->player->y * TILE_PX) - 50;
	if (++active_timer >= active_amount)
	{
		active_timer = 0;
		game_object->hud->is_dialogue_displayed = false;
		hide_dialogues(game_object);
	}
}

/**
 * @brief Loops through the array of dialogues that hides them all.
 * @param game_object The game object which holds all the dialogues.
 */
static void	hide_dialogues(t_game *game_object)
{
	int	i;

	i = 0;
	while (i < game_object->hud->dialogue_img->num_sprites)
	{
		game_object->hud->dialogue_img->animated_sprite[i]->enabled = false;
		i++;
	}
}
