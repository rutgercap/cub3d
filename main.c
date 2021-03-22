/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 18:11:34 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/15 13:02:34 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_error(char const *str)
{
	if (str)
		printf("Error: \n%s\n", str);
	exit(EXIT_FAILURE);
}

int 	main(int argc, char **argv)
{
	t_game		game;

	if (argc == 1)
		return (exit_error("No map provided"));
	if (argc > 2)
		return (exit_error("Invalid map provided"));
	// if argc > 3
	// save bmp
	if (read_file(argv[1], &game) == EXIT_FAILURE)
		return (exit_error("Invalid map provided"));
	if (init_game(&game) == EXIT_FAILURE)
		return (exit_error("Failed to start game"));
	if (load_textures(&game.textures, game.win.mlx) == EXIT_FAILURE)
		return (exit_error("Failed to load one or more texture(s)"));
	if (save_sprites(&game.map.sprites, game.map) == EXIT_FAILURE)
		return (exit_error("Malloc error saving sprites"));
	mlx_hook(game.win.win, X_EVENT_KEY_PRESS, 0, key_press, &game);
	mlx_hook(game.win.win, X_EVENT_KEY_RELEASE, 0, key_release, &game);
	mlx_loop_hook(game.win.mlx, mlx_main_loop, &game);
	mlx_loop(game.win.mlx);
	return (EXIT_SUCCESS);
}
