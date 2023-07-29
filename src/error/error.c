/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:31:49 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/29 20:38:11 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	cleanup_and_exit(t_exit_type exit_type, char *error_msg)
{
	if (exit_type == FAIL)
		ft_printf("Error:\n%s\n", error_msg);
	exit(exit_type);
}
