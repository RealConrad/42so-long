/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:57:20 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 14:54:45 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

/*
TODO: Fix makefile when installing library/mlx
TODO: Install glfw properly etc...
*/

int	main(int argc, char **argv)
{
	t_game *game_object;

	game_object = ft_calloc(1, sizeof(t_game));
	if (!game_object)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for game object.");
	if (argc != 2)
		cleanup_and_exit(game_object, FAIL, "There should only be 2 command line arguments.");

	init_game(game_object, argv[1]);
	mlx_loop(game_object->mlx);
	cleanup_and_exit(game_object, SUCCESS, "");
	return (SUCCESS);
}
