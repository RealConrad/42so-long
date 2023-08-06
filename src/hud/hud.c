/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:24:15 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/06 16:41:30 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Initializes the HUD and assigns/allocates data/memory to hud object.
 * @param game_object The game object that contains the hud.
 */
void	init_hud(t_game *game_object)
{
	game_object->hud->is_game_paused = false;
	game_object->hud->dialogue_img = ft_calloc(1, sizeof(t_animated_mob));
	if (!game_object->hud->dialogue_img)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for dialogue image.");
	
	game_object->hud->dialogue_img->num_sprites = DIALOGUE_SPRITE_COUNT;
	if (allocate_mob_object(game_object->hud->dialogue_img) == FAIL)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for dialogue image.");

	game_object->hud->is_dialogue_displayed = false;
	game_object->hud->dialogue_img->frame_skip_counter = 0;
	game_object->hud->dialogue_img->frame_skip_amount = 500;
	game_object->hud->dialogue_img->sprite_path = DIALOGUE_PATH;
	game_object->hud->dialogue_img->width = 128;
	game_object->hud->dialogue_img->height = 64;
	game_object->hud->dialogue_img->x = (game_object->player->x * TILE_PX) + 20;
	game_object->hud->dialogue_img->y = (game_object->player->y * TILE_PX) - 50;
	assign_sprite_textures(game_object->hud->dialogue_img);
	assign_sprite_images(game_object, game_object->hud->dialogue_img);
	assign_z_index(game_object->hud->dialogue_img, 5);
}

/**
 * @brief Displays the number of moves the player has made.
 * @param param A void pointer that gets type casted to (t_game *)
 */
void	display_player_move_count(void *param)
{
	t_game	*game_object;
	char	*str;
	char	*moves;
	
	game_object = (t_game *)param;
	if (game_object->hud->is_game_paused)
		return ;
	moves = ft_itoa(game_object->hud->num_player_moves);
	str = ft_strjoin("Moves: ", moves);
	if (game_object->hud->player_moves_img)
		mlx_delete_image(game_object->mlx, game_object->hud->player_moves_img);
	if (game_object->hud->has_player_moved)
	{
		game_object->hud->has_player_moved = false;
		ft_printf("%s\n", str);
	}
	game_object->hud->player_moves_img = mlx_put_string(game_object->mlx, str, 0, 0);
	game_object->hud->player_moves_img->instances->y += 10;
	game_object->hud->player_moves_img->instances->x += 10;
	free(str);
	free(moves);
}

/**
 * @brief Ends the game. It also freezes the game displays a relevant message to
 * 		  the screen depending on if the player won or lost.
 * @param game_object The game object that holds all game related data.
 * @param game_over_type The game over type if the player lost or completed the game.
 */
void	end_game(t_game *game_object, t_game_over_type game_over_type)
{
	game_object->hud->is_game_paused = true;
	if (game_over_type == DIED)
		render_game_over_screen(game_object, "You Died! Game Over!");
	else if (game_over_type == COMPLETED)
		render_game_over_screen(game_object, "For the Queen, we have claimed victory!");
}
