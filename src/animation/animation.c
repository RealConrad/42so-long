/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:02:57 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/29 20:42:36 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

static void	animate_collectables(t_collectables *collectable);

void	init_animation(void	*param)
{
	t_game			*game_object;
	static double	time = TIME_FOR_FRAME;

	game_object = (t_game *)param;
	time -= game_object->mlx->delta_time;
	if (time > 0)
		return;
	time = TIME_FOR_FRAME;
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
		// Only animate coins that haven't been collected yet
		if (!temp->is_collected)
			animate_sprite(temp->coin);
		first_iteration = false;
		temp = temp->next;
	}
}
