/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:02:57 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/29 18:04:24 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

static void	animate_collectables(t_collectables *collectable);

void	init_animation(void	*param)
{
	t_game			*game_object;

	game_object = (t_game *)param;
	// Animate player
	animate_sprite(game_object->player);
	// Animate collectables
	animate_collectables(game_object->map->collectables);
}

static void	animate_collectables(t_collectables *collectable)
{
	bool			first_iteration;
	t_collectables	*temp;

	first_iteration = true;
	temp = collectable;
	// Loop through the entire linked list and animate each node
	while (first_iteration || temp != collectable)
	{
		animate_sprite(temp->mob);
		first_iteration = false;
		temp = temp->next;
	}
}
