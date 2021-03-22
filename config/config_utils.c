/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 16:48:38 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/08 12:46:26 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int		xy_to_map(const int x, const int y, const t_map map)
{
	if (x < 1 || x > map.width || y < 1 || y > map.height)
		return (OPEN);
	return (map.map[y - 1][x - 1]);
}

int		ascii_to_dir(t_player *player)
{
	if (player->dir_x == 0)
		return (EXIT_FAILURE);
	else if (player->dir_x == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (player->dir_x == 'E')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (player->dir_x == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}	
	else if (player->dir_x == 'W')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}	
	return (EXIT_SUCCESS);
}