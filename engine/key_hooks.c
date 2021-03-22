/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hooks.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 10:12:58 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/15 13:23:35 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int		key_press(const int keycode, t_game *game)
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
	return (EXIT_SUCCESS);
}

int		key_release(const int keycode, t_game *game)
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
		if (xy_to_map(player->x - player->plane_x * move_speed , \
									player->y, map) != '1')
			player->x -= player->plane_x * move_speed;
		if (xy_to_map(player->x, player->y - \
									player->plane_y * move_speed, map) != '1')
			player->y -= player->plane_y * move_speed;
	}
}

void	turn_right_left(t_player *player, const int key)
{
	double	old_dir;
	double	old_plane;
	double	speed;

	speed = player->rot_speed;
	old_dir = player->dir_x;
	old_plane = player->plane_x;
	if (key == KEY_LEFT)
	{
		player->dir_x = player->dir_x * cos(-speed) - player->dir_y * sin(-speed);
		player->dir_y = old_dir * sin(-speed) + player->dir_y * cos(-speed);
		player->plane_x = player->plane_x * cos(-speed) - player->plane_y * sin(-speed);
		player->plane_y = old_plane * sin(-speed) + player->plane_y * cos(-speed);
	}
	else
	{
		player->dir_x = player->dir_x * cos(speed) - player->dir_y * sin(speed);
		player->dir_y = old_dir * sin(speed) + player->dir_y * cos(speed);
		player->plane_x = player->plane_x * cos(speed) - player->plane_y * sin(speed);
		player->plane_y = old_plane * sin(speed) + player->plane_y * cos(speed);
	}
}
