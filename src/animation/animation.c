/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:02:57 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/26 17:30:27 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

// can only draw 1 image per frame.
void	init_animation(void	*param)
{
	static int	frame_count = 0;
	t_game	*game_object;

	game_object = (t_game *)param;

	ft_printf("%d\n", game_object->map->num_collectables);
	if (frame_count == 0)
		animate_sprite(game_object, game_object->player);
	else if (frame_count <= game_object->map->num_collectables)
		animate_sprite(game_object, game_object->map->collectables[frame_count - 1]);
	frame_count++;
	if (frame_count > game_object->map->num_collectables)
		frame_count = 0;
	
	if (game_object->map->num_collectables == 0)
		ft_printf("Open door!");
}
