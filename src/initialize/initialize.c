/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:56:56 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/14 14:58:49 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_player(t_game *game_object);
static void update_game_state(t_game *game_object);

void	init_game(t_game *game_object)
{
	game_object->mlx = mlx_init(WIDTH, HEIGHT, "Game", true);

	// init_map(); 
	init_player(game_object);
	if (!game_object->mlx || !game_object->player)
		cleanup_and_exit(FAIL);
	update_game_state(game_object);
}

static void update_game_state(t_game *game_object)
{
	mlx_loop_hook(game_object->mlx, &loop_player_idle_animation, game_object);
	mlx_key_hook(game_object->mlx, &handle_input, game_object);
}

static void	init_player(t_game *game_object)
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
