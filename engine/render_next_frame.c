/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_next_frame.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 07:01:24 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/14 16:56:35 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

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
		draw_sprites(img, *game, z_buffer);
	mlx_put_image_to_window(game->win.mlx, game->win.win, img->img, 0, 0);
}

int		mlx_main_loop(t_game *game)
{
	static int 	update;
	
	update = 0;
	if (game->strafe != -1)
	{
		move_left_right(&game->player, game->strafe, game->map);
		update = 1;
	}
	if (game->move != -1)
	{
		move_forward_backward(&game->player, game->move, game->map);
		update = 1;
	}
	if (game->rotate != -1)
	{
		turn_right_left(&game->player, game->rotate);
		update = 1;
	}	
	if (update == 1)
	{
		if (game->frame_counter % 2 == 0)
		{
			generate_image(game, &game->img_1);
			update = 0;
		}	
		else
		{
			generate_image(game, &game->img_2);
			update = 0;
		}	
	}	
	game->frame_counter += 1;
	return (EXIT_SUCCESS);
}
