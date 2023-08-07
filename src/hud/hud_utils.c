/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:25:15 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 18:47:58 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_background(t_game *game_object);

/**
 * @brief Creates the game over screen and prints out the str to the scren.
 * @param game_object The game object that holds all game related data.
 * @param str The string to be displayed on the game over screen.
 */
void	render_game_over_screen(t_game *game_object, char *str)
{
	int	start_y;
	int	start_x;

	render_background(game_object);
	start_x = ((game_object->map->width * TILE_PX) - (ft_strlen(str) * 10)) / 2;
	start_y = ((game_object->map->height * TILE_PX) - 20) / 2;
	game_object->hud->game_over_text_img = mlx_put_string(game_object->mlx,
			str, start_x, start_y);
}

/**
 * @brief Creates a semi transparent white background that covers the entire game
 * @param game_object The game object that holds all game related data.
 */
static void	render_background(t_game *game_object)
{
	unsigned int	i;
	unsigned int	white;

	i = 0;
	white = 0xFFFFFF99;
	game_object->hud->hud_bg_image = mlx_new_image(game_object->mlx,
			game_object->map->width * TILE_PX, game_object->map->height
			* TILE_PX);
	if (!game_object->hud->hud_bg_image)
		cleanup_and_exit(game_object, FAIL, "Failed to create HUD image.");
	while (i < game_object->hud->hud_bg_image->width
		* game_object->hud->hud_bg_image->height * sizeof(int32_t))
	{
		game_object->hud->hud_bg_image->pixels[i] = white;
		i++;
	}
	mlx_image_to_window(game_object->mlx, game_object->hud->hud_bg_image, 0, 0);
	game_object->hud->hud_bg_image->instances[0].z = 69;
}
