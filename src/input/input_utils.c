/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:55:12 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 18:58:12 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Checks if the key pressed is WASD.
 * @param keydata Contains information about the key that is pressed.
 * @return Returns true if the key pressed is WASD, else false.
 */
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
