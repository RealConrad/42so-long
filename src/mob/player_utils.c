/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:15:12 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/28 13:26:16 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_player_object(t_animated_mob *player)
{
	player->sprite_path = ft_calloc(1, sizeof(char) * ft_strlen(PLAYER_SPRITE_PATH) + 1);
	if (!player->sprite_path)
		cleanup_and_exit(FAIL, "Failed to allocate memory for player sprite path.");

	player->sprites = ft_calloc(PLAYER_SPRITE_COUNT, sizeof(mlx_texture_t *) * PLAYER_SPRITE_COUNT);
	if (!player->sprites)
		cleanup_and_exit(FAIL, "Failed to allocate memory for player sprites.");
}

void	assign_player_object(t_game *game_object)
{
	int 	i;
	char 	*filename;

	i = 0;
	game_object->player->sprite_path = PLAYER_SPRITE_PATH;
	game_object->player->num_sprites = PLAYER_SPRITE_COUNT;
	game_object->player->width = PLAYER_WIDTH_PX;
	game_object->player->height = PLAYER_HEIGHT_PX;
	game_object->player->frame_skip_amount = 8;
	game_object->player->curr_frame = 0;
	game_object->player->frame_skip_counter = 0;
	game_object->player->blank_sprite = mlx_load_png(BLANK_SPRITE);
	game_object->player->img = mlx_texture_to_image(game_object->mlx, game_object->player->blank_sprite);
	while (i < PLAYER_SPRITE_COUNT)
	{
		filename = get_sprites(i, game_object->player);
		game_object->player->sprites[i] = mlx_load_png(filename);
		free(filename); // free memory allocated by get_sprites()
		i++;
	}
}
