/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:24:17 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 14:46:21 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_game *game_object, int y, int x, char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		cleanup_and_exit(game_object, FAIL, "Failed to load map texture.");
	game_object->map->map_img = mlx_texture_to_image(game_object->mlx, texture);
	mlx_delete_texture(texture);
	mlx_resize_image(game_object->map->map_img, TILE_PX, TILE_PX);
	mlx_image_to_window(game_object->mlx, game_object->map->map_img, x, y);
	mlx_set_instance_depth(game_object->map->map_img->instances, 1);
}
