/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:55:12 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/18 14:03:04 by cwenz            ###   ########.fr       */
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

bool	is_wall(t_game *game_object)
{
	// if (game_object)
	(void)game_object;
	return (false);
}

void	count_moves()
{
	static int	moves = 0;

	ft_printf("%d\n", ++moves);
}
