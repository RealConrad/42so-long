/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:49 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/30 15:36:59 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	cleanup_and_exit(t_game *game_object, t_exit_type exit_type, char *error_msg)
{
	free_game_memory(game_object);
	if (exit_type == FAIL)
		ft_printf("Error:\n%s\n", error_msg);
	exit(exit_type);
}
