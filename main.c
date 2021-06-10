/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 18:11:34 by rcappend      #+#    #+#                 */
/*   Updated: 2021/05/28 10:46:11 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	exit_error(char const *str)
{
	if (str)
		printf("Error: \n%s\n", str);
	exit(EXIT_FAILURE);
}

static void	set_struct_values(t_game *game)
{
	game->strafe = -1;
	game->move = -1;
	game->rotate = -1;
	game->player.move_speed = 0.04;
	game->player.rot_speed = 0.05;
}

static void	start_game(t_game *game)
{
	set_struct_values(game);
	mlx_hook(game->win.win, X_EVENT_KEY_PRESS, 0, key_press, game);
	mlx_hook(game->win.win, X_EVENT_KEY_RELEASE, 0, key_release, game);
	mlx_loop_hook(game->win.mlx, mlx_main_loop, game);
	mlx_loop(game->win.mlx);
}

int	main(int argc, char **argv)
{
	t_game		game;

	game.save = FALSE;
	if (argc == 1)
		return (exit_error("No map provided"));
	else if (argc > 3)
		return (exit_error("Invalid arguments given"));
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 8) == 0)
			game.save = TRUE;
		else
			exit_error("Invalid arguments given");
	}
	read_file(argv[1], &game);
	init_mlx(&game);
	load_textures(&game.textures, game.win.mlx);
	save_sprites(&game.map.sprites, game.map);
	if (game.save == FALSE)
		start_game(&game);
	else
		save_bmp(&game);
	return (EXIT_SUCCESS);
}
