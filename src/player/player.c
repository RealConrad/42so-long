/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:14:32 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/17 17:49:07 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_game *game_object, int y, int x)
{
	int		i;
	char	*filename;

	i = 0;
	game_object->player = ft_calloc(sizeof(t_player), 1);
	if (!game_object->player)
		cleanup_and_exit(FAIL, "Failed to allocate memory for player.");

	game_object->player->sprites = ft_calloc(sizeof(mlx_texture_t *) * PLAYER_SPRITE_COUNT, 1);
	if (!game_object->player->sprites)
		cleanup_and_exit(FAIL, "Failed to allocate memory for player sprites");
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
	mlx_image_to_window(game_object->mlx, game_object->player->img, x, y);
}
