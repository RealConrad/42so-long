/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:36:44 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/13 20:31:45 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*get_player_sprites(int	sprite_index)
{
	char	*filename;
	char	*frame_number_str;
	
	filename = malloc(sizeof(char) * FILENAME_SIZE);
	if (!filename)
		cleanup_and_exit(FAIL);
	frame_number_str = ft_itoa(sprite_index);
	
	// We use strlcpy first since malloc does not initialize the memory it allocates, 
	// meaning it contains random data. When you try to concatenate onto filename, the 
	// function doesn't know where the existing string ends, resulting in undefined behavior.
	ft_strlcpy(filename, PLAYER_SPRITE_PATH, FILENAME_SIZE);
	ft_strlcat(filename, frame_number_str, FILENAME_SIZE);
	ft_strlcat(filename, ".png", FILENAME_SIZE);
	
	free(frame_number_str); // Free memory allocated by ft_itoa()
	return (filename);
}

void	loop_player_idle_animation(void *param)
{
	t_game *game_object;
	
	game_object = (t_game *)param;

	game_object->player->curr_frame = (game_object->player->curr_frame + 1) % MAX_SPRITES;
	printf("%d\n", game_object->player->curr_frame);
	game_object->player->img = mlx_texture_to_image(game_object->mlx, game_object->player->sprites[game_object->player->curr_frame]);
}
