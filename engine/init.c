/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/31 12:32:25 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/10 14:31:50 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int	init_window(t_mlx *win)
{
	int		screen_x;
	int		screen_y;
	
	win->mlx = mlx_init();
	if (!win->mlx)
		return (EXIT_FAILURE);
	mlx_get_screen_size(win->mlx, &screen_x, &screen_y);
	if (win->res_x > screen_x)
		win->res_x = screen_x;
	if (win->res_y > screen_y)
		win->res_y = screen_y;
	win->win = mlx_new_window(win->mlx, win->res_x, win->res_y, "cub3d");
	if (!win->win)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	init_image(t_image *img, const t_mlx *win)
{
	img->img = mlx_new_image(win->mlx, win->res_x, win->res_y);
	if (!img->img)
		return (EXIT_FAILURE);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,\
				&img->endian);
	if (!img->addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	set_struct_values(t_game *game)
{
	game->strafe = -1;
	game->move = -1;
	game->rotate = -1;
	game->player.plane_x = 0;
	game->player.plane_y = 0.5;
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.02;
}

int		init_game(t_game *game)
{
	int error;

	error = 0;
	error = init_window(&game->win);
	if (!error)
		error = init_image(&game->img_1, &game->win);
	if (!error)
		error = init_image(&game->img_2, &game->win);
	if (!error)
		set_struct_values(game);
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
