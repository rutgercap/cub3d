/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_next_frame.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 07:01:24 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/25 12:25:39 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
** Three steps for generating frames:
** 1: Casting ray
** 2: Drawing walls, floor and ceiling based on ray
** 3: Drawing sprites if found
*/

static void		generate_image(t_game *game, t_image *img)
{
	t_ray		ray;
	int			sprites_found;
	double		z_buffer[game->win.res_x];
	int			x;

	x = 0;
	sprites_found = 0;
	while (x < game->win.res_x)
	{
		ray.x = x;
		raycaster(&ray, *game, &sprites_found, &z_buffer[x]);
		draw_room(img, *game, ray);
		x++;
	}
	if (sprites_found > 0)
		draw_sprites(img, &game->map.sprites, *game, z_buffer);
	mlx_put_image_to_window(game->win.mlx, game->win.win, img->img, 0, 0);
}

/*
** Main Loop consists of checking for movement and then rendering next frame
*/

int				mlx_main_loop(t_game *game)
{	
	if (game->strafe != -1)
		move_left_right(&game->player, game->strafe, game->map);
	if (game->move != -1)
		move_forward_backward(&game->player, game->move, game->map);
	if (game->rotate != -1)
		turn_right_left(&game->player, game->rotate);
	if (game->frame_counter % 2 == 0)
		generate_image(game, &game->img_1);
	else
		generate_image(game, &game->img_2);
	game->frame_counter += 1;
	return (EXIT_SUCCESS);
}
