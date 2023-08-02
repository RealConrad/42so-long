/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:24:15 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/02 16:03:53 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_hud(t_game *game_object)
{
	game_object->hud->is_game_paused = false;
}

void	display_player_move_count(void *param)
{
	t_game	*game_object;
	char	*str;
	char	*moves;
	
	game_object = (t_game *)param;
	if (game_object->hud->is_game_paused)
		return ;
	moves = ft_itoa(game_object->hud->num_player_moves);
	str = ft_strjoin("Moves: ", moves);
	if (game_object->hud->player_moves_img)
		mlx_delete_image(game_object->mlx, game_object->hud->player_moves_img);
	if (game_object->hud->has_player_moved)
	{
		game_object->hud->has_player_moved = false;
		ft_printf("%s\n", str);
	}
	game_object->hud->player_moves_img = mlx_put_string(game_object->mlx, str, 0, 0);
	game_object->hud->player_moves_img->instances->y += 10;
	game_object->hud->player_moves_img->instances->x += 10;
	free(str);
	free(moves);
}

void	end_game(t_game *game_object, t_game_over_type game_over_type)
{
	game_object->hud->is_game_paused = true;
	if (game_over_type == DIED)
		render_game_over_screen(game_object, "You Died! Game Over!");
	else if (game_over_type == COMPLETED)
		render_game_over_screen(game_object, "For the Queen, we have claimed victory!");
}
