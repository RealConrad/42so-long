/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:57:20 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/11 17:37:54 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_game *game_object;
	
	game_object = malloc(sizeof(t_game));
	if (!game_object)
		cleanup_and_exit();
	
	init_game(game_object);
	mlx_key_hook(game_object->mlx, &handle_input, game_object);
	
	mlx_loop(game_object->mlx);
	ft_printf("Shutting down now... 〈◕﹏◕〉");
	return (EXIT_SUCCESS);
}
