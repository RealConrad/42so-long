/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:08:25 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/27 13:40:41 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	init_collectable(t_game *game_object, int y, int x)
{
	t_collectables	*new_collectable;
	t_collectables	*curr_collectable;
	
	new_collectable = ft_calloc(1, sizeof(t_collectables));
	if (!new_collectable)
		cleanup_and_exit(FAIL, "Failed to allocate memory for new collectable.");
	new_collectable->mob = ft_calloc(1, sizeof(t_animated_mob));
	if (!new_collectable->mob)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable mob.");
	
	// Allocate memory for collectable struct
	allocate_collectable_object(new_collectable->mob);
	// Assign values for collectables
	assign_collectable_object(game_object, new_collectable->mob);
	new_collectable->next = NULL;
	// If linked list has not been initialized yet
	if (!game_object->map->collectables)
		game_object->map->collectables = new_collectable;
	else
	{
		curr_collectable = game_object->map->collectables;
		while (curr_collectable->next)
			curr_collectable = curr_collectable->next;
		curr_collectable->next = new_collectable;
	}
	mlx_image_to_window(game_object->mlx, new_collectable->mob->img, x, y);
}
