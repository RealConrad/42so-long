/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:02:57 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/27 13:10:26 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

// can only draw 1 image per frame.
void	init_animation(void	*param)
{
	static int		frame_count = 0;
	t_game			*game_object;
	int				i;
	t_collectables	*curr_collectable;

	game_object = (t_game *)param;

	if (frame_count == 0)
		animate_sprite(game_object, game_object->player);
	else if (frame_count <= game_object->map->num_collectables)
	{
		curr_collectable = game_object->map->collectables;
		i = 1;
		while (curr_collectable && i++ < frame_count)
			curr_collectable = curr_collectable->next;
		if (curr_collectable)
			animate_sprite(game_object, curr_collectable->mob);
	}
	frame_count++;
	if (frame_count > game_object->map->num_collectables)
		frame_count = 0;
	
	if (game_object->map->num_collectables == 0)
		ft_printf("Open door!");
}
