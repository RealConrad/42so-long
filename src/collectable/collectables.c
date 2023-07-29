/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:08:25 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/29 19:37:02 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	init_collectable(t_game *game_object, int y, int x)
{
	t_collectables	*new_collectable;

	new_collectable = ft_calloc(1, sizeof(t_collectables));
	if (!new_collectable)
		cleanup_and_exit(FAIL, "Failed to allocate memory for new collectable.");
	new_collectable->coin = ft_calloc(1, sizeof(t_animated_mob));
	if (!new_collectable->coin)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable mob.");

	// Allocate memory for collectable struct
	allocate_collectable_object(new_collectable->coin);
	// Assign values for collectables
	assign_collectable_object(game_object, new_collectable->coin, y, x);
	// Add the collectable to linked list
	add_collectable_node(game_object, new_collectable);
}
