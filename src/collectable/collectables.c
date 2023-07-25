/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:08:25 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/25 14:42:36 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	init_collectable(t_game *game_object, int y, int x)
{
	int	i;

	i = 0;
	while (game_object->map->collectables[i])
		i++;
	
	game_object->map->collectables[i] = ft_calloc(sizeof(t_animated_mob), 1);
	if (!game_object->map->collectables)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable");

	// Allocate memory for collectable struct
	allocate_collectable_object(game_object->map->collectables[i]);
	// Assign values for collectables
	assign_collectable_object(game_object, i);

	mlx_image_to_window(game_object->mlx, game_object->map->collectables[i]->img, x, y);
}
