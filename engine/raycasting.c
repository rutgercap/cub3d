/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/09 09:23:45 by rcappend      #+#    #+#                 */
/*   Updated: 2021/04/27 11:18:13 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	calc_dir_and_delta(t_ray *ray, const t_player player)
{
	ray->raydir_x = player.dir_x + player.plane_x * ray->camera_x;
	ray->raydir_y = player.dir_y + player.plane_y * ray->camera_x;
	ray->map_x = player.x;
	ray->map_y = player.y;
	if (ray->raydir_y == 0)
		ray->deltadist_x = 0;
	else if (ray->raydir_x == 0)
		ray->deltadist_x = 1;
	else
		ray->deltadist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_x == 0)
		ray->deltadist_y = 0;
	else if (ray->raydir_y == 0)
		ray->deltadist_y = 1;
	else
		ray->deltadist_y = fabs(1 / ray->raydir_y);
}

static void	calc_side_dist(t_ray *ray, const t_player player)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player.x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player.x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player.y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player.y) * ray->deltadist_y;
	}
}

static void	cast_ray(t_ray *ray, const t_map map, int *sprites)
{
	t_bool		hit;
	char		found;

	hit = FALSE;
	while (hit == FALSE)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		found = xy_to_map(ray->map_x, ray->map_y, map);
		if (found == SPRITE)
			*sprites += 1;
		else if (found == WALL)
			hit = TRUE;
	}
}

void	raycaster(t_ray *ray, const t_game game, \
					int *sprites, double *distance)
{
	ray->camera_x = 2 * ray->x / (double)game.win.res_x - 1;
	calc_dir_and_delta(ray, game.player);
	calc_side_dist(ray, game.player);
	cast_ray(ray, game.map, sprites);
	if (ray->side == 0)
		ray->distance = fabs((ray->map_x - game.player.x + \
						(1 - ray->step_x) / 2) / ray->raydir_x);
	else
		ray->distance = fabs((ray->map_y - game.player.y + \
						(1 - ray->step_y) / 2) / ray->raydir_y);
	*distance = ray->distance;
}
