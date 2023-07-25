/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:55:12 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/25 17:34:26 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_movement(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W
			|| keydata.key == MLX_KEY_A
			|| keydata.key == MLX_KEY_S
			|| keydata.key == MLX_KEY_D
		)
		return (true);
	return (false);
}

void	remove_collectable(t_game *game_object)
{
	int	i;

	i = 0;
	while (i < game_object->map->num_collectables)
	{
		if (game_object->map->collectables[i]->x == game_object->player->x
			&& game_object->map->collectables[i]->y == game_object->player->y)
		{
			deallocate_collectable_object(game_object, i);
			ft_memmove(game_object->map->collectables[i],
				game_object->map->collectables[i + 1],
				(game_object->map->num_collectables - i - 1) * sizeof(t_animated_mob));
			game_object->map->num_collectables--;
			break ;
		}
		i++;
	}
}

void	count_moves()
{
	static int	moves = 0;

	ft_printf("%d\n", ++moves);
}
