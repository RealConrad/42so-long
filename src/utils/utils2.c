/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:28:30 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/01 14:52:03 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

bool	allocate_mob_object(t_animated_mob *mob)
{
	mob->sprites = ft_calloc(mob->num_sprites, sizeof(mlx_texture_t *) * mob->num_sprites + 1);
	if (!mob->sprites)
		return (FAIL);

	mob->animated_sprite = ft_calloc(mob->num_sprites, sizeof(mlx_image_t *) * mob->num_sprites + 1);
	if (!mob->animated_sprite)
		return (FAIL);

	return (SUCCESS);
}