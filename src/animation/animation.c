/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:02:57 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/29 17:29:30 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

// can only draw 1 image per frame.
void	init_animation(void	*param)
{
	t_game			*game_object;
	bool			first_iteration;
	t_collectables	*temp;

	game_object = (t_game *)param;
	temp = game_object->map->collectables;
	first_iteration = true;

	animate_sprite(game_object->player);
	while (first_iteration || temp != game_object->map->collectables)
	{
		// ft_printf("Animating collectable!\n");
		animate_sprite(temp->mob);
		first_iteration = false;
		temp = temp->next;
	}
}

// void	init_animation(void	*param)
// {
// 	static int		frame = 0;
// 	t_game			*game_object;
// 	t_collectables	*curr_collectable;
// 	int				total;
// 	int				i;

// 	game_object = (t_game *)param;
// 	total = 1 + game_object->map->num_collectables;

// 	// loop through player
// 	if (frame == 0)
// 		animate_sprite(game_object, game_object->player);
// 	else
// 	{
// 		i = 1;
// 		curr_collectable = game_object->map->collectables;
// 		while (i < frame % total && curr_collectable)
// 		{
// 			curr_collectable = curr_collectable->next;
// 			i++;
// 		}
// 		if (curr_collectable)
// 			animate_sprite(game_object, curr_collectable->mob);
// 	}
// 	frame++;
// 	if (frame >= total)
// 		frame = 0;
// 	if (game_object->map->num_collectables == 0)
// 		ft_printf("Open door!");
// }
