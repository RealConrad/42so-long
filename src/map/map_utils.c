/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:24:17 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/21 15:24:46 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_game *game_object, int y, int x, char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		cleanup_and_exit(EXIT_FAILURE, "Failed to load map texture.");
	game_object->map->map_img = mlx_texture_to_image(game_object->mlx, texture);
	mlx_resize_image(game_object->map->map_img, TILE_PX, TILE_PX);
	mlx_delete_texture(texture);
	mlx_image_to_window(game_object->mlx, game_object->map->map_img, x, y);
	game_object->map->map_img->instances[0].z = 0;
}

void	print_map(t_game *game_object)
{
	int i;

	i = 0;
	ft_printf("MAP:\n");
	while(game_object->map->map_plan[i])
		ft_printf("%s", game_object->map->map_plan[i++]);
}
