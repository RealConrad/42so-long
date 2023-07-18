/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:34:22 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/18 13:09:31 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_movement(t_game *game_object, mlx_key_data_t keydata);

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game_object;

	game_object = (t_game *)param;
	if (is_movement(keydata) && !is_wall(game_object))
		handle_movement(game_object, keydata);
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game_object->mlx);
}

static void	handle_movement(t_game *game_object, mlx_key_data_t keydata)
{
	(void)keydata;

	// MLX42 the x/y axis are inversed, hence we do '-=' for W
	if (mlx_is_key_down(game_object->mlx, MLX_KEY_W))
	{
		game_object->player->img->instances[0].y -= MOVE_SPEED;
		// game_object->map->
	}
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_S))
	{
		game_object->player->img->instances[0].y += MOVE_SPEED;
		
	}
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_A))
	{
		game_object->player->img->instances[0].x -= MOVE_SPEED;

	}
	else if (mlx_is_key_down(game_object->mlx, MLX_KEY_D))
	{
		game_object->player->img->instances[0].x += MOVE_SPEED;
		
	}
	count_moves();
}
