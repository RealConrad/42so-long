/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:14:32 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/14 17:17:32 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_game *game_object)
{
	int		i;
	char	*filename;

	i = 0;
	game_object->player = malloc(sizeof(t_player));
	if (!game_object->player)
		cleanup_and_exit(FAIL);

	game_object->player->sprites = malloc(sizeof(mlx_texture_t *) * PLAYER_SPRITE_COUNT);
	if (!game_object->player->sprites)
		cleanup_and_exit(FAIL);
	while (i < PLAYER_SPRITE_COUNT)
	{
		filename = get_player_sprites(i);
		game_object->player->sprites[i] = mlx_load_png(filename);
		free(filename); // free memory allocated by get_player_sprites
		i++;
	}
	game_object->player->curr_frame = 0;
	game_object->player->blank_sprite = mlx_load_png(BLANK_PLAYER_IMAGE);
	game_object->player->img = mlx_texture_to_image(game_object->mlx, game_object->player->blank_sprite);
	mlx_image_to_window(game_object->mlx, game_object->player->img, 0, 0);
}
