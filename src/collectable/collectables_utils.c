/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:12:40 by cwenz             #+#    #+#             */
/*   Updated: 2023/07/29 17:34:18 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_collectable_object(t_animated_mob *collectable)
{
	collectable->sprite_path = ft_calloc(1, sizeof(char) * ft_strlen(COLLECTABLE_PATH) + 1);
	if (!collectable->sprite_path)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable sprite path.");

	collectable->sprites = ft_calloc(COLLECTABLE_SPRITE_COUNT, sizeof(mlx_texture_t *) * COLLECTABLE_SPRITE_COUNT + 1);
	if (!collectable->sprites)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable sprites.");
	collectable->animated_sprite = ft_calloc(COLLECTABLE_SPRITE_COUNT, sizeof(mlx_texture_t *) * COLLECTABLE_SPRITE_COUNT + 1);
	if (!collectable->sprites)
		cleanup_and_exit(FAIL, "Failed to allocate memory for collectable sprites.");
}

void	assign_collectable_object(t_game *game_object, t_animated_mob *collectable, int y, int x)
{
	int		i;
	char	*filename;

	i = 0;
	collectable->sprite_path = COLLECTABLE_PATH;
	collectable->num_sprites = COLLECTABLE_SPRITE_COUNT;
	collectable->width = COLLECTABLE_WIDTH_PX;
	collectable->height = COLLECTABLE_HEIGHT_PX;
	collectable->frame_skip_amount = 6;
	collectable->curr_frame = 0;
	collectable->frame_skip_counter = 0;
	collectable->x = x / TILE_PX;
	collectable->y = y / TILE_PX;
	while (i < COLLECTABLE_SPRITE_COUNT)
	{
		filename = get_sprites(i, collectable);
		collectable->sprites[i] = mlx_load_png(filename);
		free(filename); // free memory allocated by get_sprites()
		i++;
	}
	collectable->sprites[i] = NULL;
	i = 0;
	while (i < COLLECTABLE_SPRITE_COUNT)
	{
		collectable->animated_sprite[i] = mlx_texture_to_image(game_object->mlx, collectable->sprites[i]);
		mlx_resize_image(collectable->animated_sprite[i], collectable->width, collectable->height);
		collectable->animated_sprite[i]->enabled = false;
		mlx_image_to_window(game_object->mlx, collectable->animated_sprite[i], x, y);
		i++;
	}
	collectable->animated_sprite[i] = NULL;
}

void	remove_collectable(t_game *game_object)
{
	t_collectables	*curr_collectable;
	t_collectables	*temp;

	curr_collectable = game_object->map->collectables;
	while (curr_collectable->next)
	{
		if (curr_collectable->mob->x == game_object->player->x
			&& curr_collectable->mob->y == game_object->player->y)
		{
			if (curr_collectable->next)
				curr_collectable->next->prev = curr_collectable->prev;
			if (curr_collectable->prev)
				curr_collectable->next->next = curr_collectable->next;
			if (game_object->map->collectables == curr_collectable)
				game_object->map->collectables = curr_collectable->next;
			
			temp = curr_collectable;
			curr_collectable = curr_collectable->next;
			game_object->map->num_collectables--;
		}
		else
			curr_collectable = curr_collectable->next;
	}
}
