/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:44:28 by cwenz             #+#    #+#             */
/*   Updated: 2023/08/07 19:31:11 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	assign_enemy_object(t_game *game_object, int y, int x);
static void	update_enemy_pos(t_game *game_object, int direction);

/**
 * @brief Initializes the enemy at the given position.
 * @param game_object The game object which holds all game related data.
 * @param y The y position (in PX) of the enemy.
 * @param x The x position (in PX) of the enemy.
 */
void	init_enemy(t_game *game_object, int y, int x)
{
	game_object->enemy = ft_calloc(1, sizeof(t_animated_mob));
	if (!game_object->enemy)
		cleanup_and_exit(game_object, FAIL,
			"Failed to allocate memory for enemy.");
	game_object->enemy->num_sprites = ENEMY_SPRITE_COUNT;
	if (allocate_mob_object(game_object->enemy) == FAIL)
		cleanup_and_exit(game_object, FAIL,
			"Failed to allocate memory for enemy object.");
	assign_enemy_object(game_object, y, x);
	assign_z_index(game_object->enemy, 4);
}

/**
 * @brief Moves the enemy in random directions
 * @param param A void pointer that gets type casted to (t_game *)
 */
void	move_enemy(void *param)
{
	t_game		*game_object;
	int			rand_num;
	static int	frame_counter = 0;
	int			frame_skip_amount;

	frame_skip_amount = 50;
	game_object = (t_game *)param;
	if (game_object->hud->is_game_paused)
		return ;
	rand_num = (rand() % 4) + 1;
	if (++frame_counter >= frame_skip_amount)
	{
		frame_counter = 0;
		if (rand_num == 1)
			update_enemy_pos(game_object, 1);
		else if (rand_num == 2)
			update_enemy_pos(game_object, 2);
		else if (rand_num == 3)
			update_enemy_pos(game_object, 3);
		else if (rand_num == 4)
			update_enemy_pos(game_object, 4);
	}
}

/**
 * @brief Assigns data tot he enemy object
 * @param game_object The game object which holds the enemy
 * @param y The y position (in PX) of the enemy
 * @param x The x position (in PX) of the enemy
 */
static void	assign_enemy_object(t_game *game_object, int y, int x)
{
	game_object->enemy->sprite_path = ENEMY_SPRITE_PATH;
	game_object->enemy->width = ENEMY_WIDTH_PX;
	game_object->enemy->height = ENEMY_HEIGHT_PX;
	game_object->enemy->frame_skip_amount = 0;
	game_object->enemy->frame_skip_counter = 0;
	game_object->enemy->offset_image_px = 15;
	game_object->enemy->curr_frame = 0;
	game_object->enemy->x = x / TILE_PX;
	game_object->enemy->y = y / TILE_PX;
	assign_sprite_textures(game_object->enemy);
	assign_sprite_images(game_object, game_object->enemy);
	assign_z_index(game_object->enemy, 4);
}

/**
 * @brief Updates the enemy position on the map. Also checks
 * 		  if the tile the enemy is going to move to is valid.
 * @param game_object The game object which holds all game related data.
 * @param direction The direction in which the enemy should move.
 */
static void	update_enemy_pos(t_game *game_object, int direction)
{
	int	delta_x;
	int	delta_y;
	int	tile_x;
	int	tile_y;

	delta_x = 0;
	delta_y = 0;
	if (direction == 1)
		delta_y = UP;
	else if (direction == 2)
		delta_y = DOWN;
	else if (direction == 3)
		delta_x = RIGHT;
	else if (direction == 4)
		delta_x = LEFT;
	tile_x = game_object->enemy->x + delta_x;
	tile_y = game_object->enemy->y + delta_y;
	if (game_object->map->map_plan[tile_y][tile_x] == GROUND
		|| game_object->map->map_plan[tile_y][tile_x] == COLLECTABLE)
	{
		game_object->enemy->x += delta_x;
		game_object->enemy->y += delta_y;
	}
}
