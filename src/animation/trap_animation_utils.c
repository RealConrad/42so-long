/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_trap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:35:36 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 11:35:47 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	animate_trap_idle(t_trap *trap, int idle_time)
{
	trap->is_active = false;
	if (++(trap->spike->frame_skip_counter) >= idle_time)
	{
		trap->spike->frame_skip_counter = 0;
		trap->spike->curr_frame++;
		trap->forward = true;
	}
}

void	animate_trap_active(t_trap *trap, int active_time)
{
	if (++(trap->spike->frame_skip_counter) >= active_time)
	{
		trap->is_active = true;
		trap->spike->frame_skip_counter = 0;
		if (trap->forward)
		{
			if (trap->spike->curr_frame >= 3)
			{
				trap->spike->curr_frame--;
				trap->forward = false;
			}
			else
				trap->spike->curr_frame++;
		}
		else
		{
			if (trap->spike->curr_frame <= 1)
				trap->spike->curr_frame--;
			else
				trap->spike->curr_frame--;
		}
	}
}
