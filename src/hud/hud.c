/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:24:15 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/02 12:58:58 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	display_player_move_count(t_game *game_object);

void	init_hud(void *param)
{
	t_game *game_object;

	game_object = (t_game *)param;
	
	display_player_move_count(game_object);

	if (game_object->hud->is_player_dead)
	{
		ft_printf("Player has died!\n");
	}
}

static void	display_player_move_count(t_game *game_object)
{
	char	*str;
	char	*moves;
	
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

void	display_game_over(t_game *game_object)
{
	(void)game_object;
	cleanup_and_exit(game_object, SUCCESS, "");
}
