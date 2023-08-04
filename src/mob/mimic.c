/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mimic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:00:53 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/04 11:48:51 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

static void	assign_mimic_object(t_game *game_object, t_animated_mob *mimic, int y, int x);
static void	add_mimic_node(t_game *game_object, t_mimic *mimic);

void	init_mimic(t_game *game_object, int y, int x)
{
	t_mimic	*mimic;

	mimic = ft_calloc(1, sizeof(t_mimic));
	if (!mimic)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for mimic.");
	mimic->chest = ft_calloc(1, sizeof(t_animated_mob));
	if (!mimic->chest)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for mimic chest.");
	
	mimic->chest->num_sprites = MIMIC_SPRITE_COUNT;
	if (allocate_mob_object(mimic->chest) == FAIL)
		cleanup_and_exit(game_object, FAIL, "Failed to allocate memory for mimic object");

	assign_mimic_object(game_object, mimic->chest, y, x);
	add_mimic_node(game_object, mimic);
}

static void	assign_mimic_object(t_game *game_object, t_animated_mob *mimic, int y, int x)
{
	mimic->sprite_path = MIMIC_SPRITE_PATH;
	mimic->width = MIMIC_WIDTH_PX;
	mimic->height = MIMIC_HEIGHT_PX;
	mimic->frame_skip_amount = 6;
	mimic->frame_skip_counter = 0;
	mimic->offset_image_px = 0;
	mimic->curr_frame = 0;
	mimic->x = x / TILE_PX;
	mimic->y = y / TILE_PX;
	assign_sprite_textures(mimic);
	assign_sprite_images(game_object, mimic);
	assign_z_index(mimic, 5);
}

static void	add_mimic_node(t_game *game_object, t_mimic *mimic)
{
	t_mimic	*curr_mimic;

	mimic->next = NULL;
	mimic->prev = NULL;
	mimic->chest->animated_sprite[0]->enabled = true;
	mimic->chest->animated_sprite[0]->instances->x = mimic->chest->x * TILE_PX + (TILE_PX / 2) - (mimic->chest->width / 2);
	mimic->chest->animated_sprite[0]->instances->y = mimic->chest->y * TILE_PX + (TILE_PX / 2) - (mimic->chest->height / 2);
	mimic->chest->animated_sprite[0]->instances->z = 3;
	// If linked list has not been initialized yet
	if (!game_object->map->mimics)
	{
		game_object->map->mimics = mimic;
		mimic->next = mimic;
		mimic->prev = mimic;	
	}
	else
	{
		curr_mimic = game_object->map->mimics;
		while (curr_mimic->next != game_object->map->mimics)
			curr_mimic = curr_mimic->next;
		curr_mimic->next = mimic;
		mimic->prev = curr_mimic;
		mimic->next = game_object->map->mimics;
		game_object->map->mimics->prev = mimic;
	}
}
