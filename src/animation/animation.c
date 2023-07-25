/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:02:57 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/25 13:34:35 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	init_animation(void	*param)
{
	t_game	*game_object;
	
	game_object = (t_game *)param;
	
	// Animate player
	// Animate collectables
	animate_sprite(game_object, game_object->map->collectables);
	// animate_sprite(game_object, game_object->player);
}
