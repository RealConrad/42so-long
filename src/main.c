/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:57:20 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/14 17:54:56 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

int	main(int argc, char **argv)
{
	(void)argv;
	t_game *game_object;
	if (argc != 2)
		cleanup_and_exit(EXIT_FAILURE);
	
	game_object = malloc(sizeof(t_game));
	if (!game_object)
		cleanup_and_exit(FAIL);

	init_game(game_object, argv[1]);
	mlx_loop(game_object->mlx);

	ft_printf("Shutting down now... 〈◕﹏◕〉");
	return (SUCCESS);
}
