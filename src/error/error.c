/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:49 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 17:06:24 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Cleans up memory and exits out of the program. If the exit_type
 * 		  is FAIL, it will display an error message.
 * @param game_object The game object which holds all game related data.
 * @param exit_type Determines if the program exits successfully or fails
 * @param error_msg The error message to be displayed, only if exit_type is fail.
 */
void	cleanup_and_exit(t_game *game_object, t_exit_type exit_type,
			char *error_msg)
{
	free_game_memory(game_object);
	if (exit_type == FAIL)
		ft_printf("Error:\n%s\n", error_msg);
	system("leaks so_long");
	exit(exit_type);
}
