/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:57:20 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/17 17:30:48 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

int	main(int argc, char **argv)
{
	t_game *game_object;
	if (argc != 2)
		cleanup_and_exit(EXIT_FAILURE, "Should only have 2 command line arguments.");
	
	game_object = ft_calloc(sizeof(t_game), 1);
	if (!game_object)
		cleanup_and_exit(FAIL, "Failed to allocate memory for game object.");

	init_game(game_object, argv[1]);
	mlx_loop(game_object->mlx);

	ft_printf("Shutting down now... 〈◕﹏◕〉");
	return (EXIT_SUCCESS);
}
