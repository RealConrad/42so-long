/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:56:56 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/11 18:40:16 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_game *game_object);

void	init_game(t_game *game_object)
{
	game_object->mlx = mlx_init(WIDTH, HEIGHT, "Game", true);

	init_player(game_object);
	// init_map(); 
	if (!game_object->mlx || !game_object->player)
		cleanup_and_exit();
		
	// mlx_image_to_window(game_object->mlx, game_object->player->img, 0, 0);
}

void	init_player(t_game *game_object)
{
	char	*filename;
	int		i;

	i = 0;
	game_object->player = malloc(sizeof(t_player));
	game_object->player->sprite = malloc(sizeof(mlx_texture_t *) * 9);
	game_object->player->img = malloc(sizeof(mlx_image_t *) * 9);
		
	// game_object->player = mlx_load_png("./assets/player/HeroKnight_Idle_0.png");
	// game_object->img = mlx_texture_to_image(game_object->mlx, game_object->player);
}
