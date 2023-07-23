/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:55:12 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/23 17:12:21 by cwenz            ###   ########.fr       */
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

void	count_moves()
{
	static int	moves = 0;

	ft_printf("%d\n", ++moves);
}
