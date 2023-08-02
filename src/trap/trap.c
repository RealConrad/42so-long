/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:40:29 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/02 10:07:04 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

/**
 * @brief Initialises a new trap and adds it to a linked list of traps.
 * @param game_object The game_object that holds game related data such as
 * 		  the linked list of traps, map etc.
 * @param y The y-axis position of the trap represented in PX value
 * @param x The x-axis position of the trap represented in PX value
 */
void	init_trap(t_game *game_object, int y, int x)
{
	t_trap	*trap;

	trap = ft_calloc(1, sizeof(t_trap));
	if (!trap)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for trap.");

	trap->spike = ft_calloc(1, sizeof(t_animated_mob));
	if (!trap->spike)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for trap spike.");

	trap->spike->num_sprites = TRAP_SPRITE_COUNT;
	if (allocate_mob_object(trap->spike) == FAIL)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for spike object");

	assign_trap_object(game_object, trap->spike, y, x);
	add_spike_node(game_object, trap);
}
