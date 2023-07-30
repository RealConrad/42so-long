/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:53:18 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/30 14:22:43 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_exit(t_game *game_object, int y, int x)
{
	mlx_texture_t	*texture;

	// Assign closed door image
	texture = mlx_load_png(EXIT_PATH);
	if (!texture)
		cleanup_and_exit(FAIL, "Failed to load closed door texture.");
	game_object->map->exit = mlx_texture_to_image(game_object->mlx, texture);
	game_object->map->exit->enabled = true;
	// Delete texture, no longer needed.
	mlx_delete_texture(texture);
	mlx_resize_image(game_object->map->exit, TILE_PX, TILE_PX);
	mlx_image_to_window(game_object->mlx, game_object->map->exit, x, y);
}
