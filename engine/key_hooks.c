/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutgercappendijk <rutgercappendijk@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 10:12:58 by rcappend          #+#    #+#             */
/*   Updated: 2021/06/10 15:03:09 by rutgercappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	key_press(const int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->move = KEY_W;
	if (keycode == KEY_A)
		game->strafe = KEY_A;
	if (keycode == KEY_S)
		game->move = KEY_S;
	if (keycode == KEY_D)
		game->strafe = KEY_D;
	if (keycode == KEY_LEFT)
		game->rotate = KEY_LEFT;
	if (keycode == KEY_RIGHT)
		game->rotate = KEY_RIGHT;
	if (keycode == KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	key_release(const int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->move = -1;
	if (keycode == KEY_A)
		game->strafe = -1;
	if (keycode == KEY_S)
		game->move = -1;
	if (keycode == KEY_D)
		game->strafe = -1;
	if (keycode == KEY_LEFT)
		game->rotate = -1;
	if (keycode == KEY_RIGHT)
		game->rotate = -1;
	return (EXIT_SUCCESS);
}

void	move_forward_backward(t_player *player, const int key, const t_map map)
{
	double	move_speed;

	move_speed = player->move_speed;
	if (key == KEY_W)
	{
		if (xy_to_map(player->x + player->dir_x * move_speed, \
						player->y, map) != '1')
			player->x += player->dir_x * move_speed;
		if (xy_to_map(player->x, player->y + player->dir_y * \
						move_speed, map) != '1')
			player->y += player->dir_y * move_speed;
	}
	else
	{
		if (xy_to_map(player->x - player->dir_x * move_speed, \
									player->y, map) != '1')
			player->x -= player->dir_x * move_speed;
		if (xy_to_map(player->x, player->y - \
									player->dir_y * move_speed, map) != '1')
			player->y -= player->dir_y * move_speed;
	}
}

void	move_left_right(t_player *player, const int key, const t_map map)
{
	double	move_speed;

	move_speed = player->move_speed;
	if (key == KEY_D)
	{
		if (xy_to_map(player->x + player->plane_x * move_speed, \
						player->y, map) != '1')
			player->x += player->plane_x * move_speed;
		if (xy_to_map(player->x, player->y + player->plane_y * \
						move_speed, map) != '1')
			player->y += player->plane_y * move_speed;
	}
	else
	{
		if (xy_to_map(player->x - player->plane_x * move_speed, \
									player->y, map) != '1')
			player->x -= player->plane_x * move_speed;
		if (xy_to_map(player->x, player->y - \
									player->plane_y * move_speed, map) != '1')
			player->y -= player->plane_y * move_speed;
	}
}

void	turn_right_left(t_player *player, const int key)
{
	double	speed;
	double	temp_x;
	double	temp_y;

	speed = player->rot_speed;
	if (key == KEY_LEFT)
		speed = -speed;
	temp_x = player->dir_x;
	temp_y = player->dir_y;
	player->dir_x = temp_x * cos(speed) - temp_y * sin(speed);
	player->dir_y = temp_x * sin(speed) + temp_y * cos(speed);
	temp_x = player->plane_x;
	temp_y = player->plane_y;
	player->plane_x = temp_x * cos(speed) \
					- temp_y * sin(speed);
	player->plane_y = temp_x * sin(speed) \
					+ temp_y * cos(speed);
}
