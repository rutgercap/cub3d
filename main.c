/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 18:11:34 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/25 12:47:12 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				exit_error(char const *str)
{
	if (str)
		printf("Error: \n%s\n", str);
	exit(EXIT_FAILURE);
}

/*
** Main consists of the five steps to start the game:
** 1:	Read the '.cub' file. This includes error checking in the map or config
**		"config/file_parser.c"
** 2:	Initialise game based on the config
**		"engine/init.c"
** 3:	Loading textures based on file paths
**		"config/load_textures.c"
** 4:	Saving sprites from the map
**		"config/sprite_utils.c"
** 5:	Initialising the mlx hooks and starting the loop (starting the game)
**		"engine/render_next_frame.c"
** If any of these steps fails, the game exits with an error message
** This automatically deallocates the memory
*/

int 			main(int argc, char **argv)
{
	t_game		game;

	if (argc == 1)
		return (exit_error("No map provided"));
	else if (argc > 2)
		return (exit_error("Invalid map provided"));
	// if argc > 3
	// save bmp
	read_file(argv[1], &game);
	init_game(&game);
	load_textures(&game.textures, game.win.mlx);
	save_sprites(&game.map.sprites, game.map);

	mlx_hook(game.win.win, X_EVENT_KEY_PRESS, 0, key_press, &game);
	mlx_hook(game.win.win, X_EVENT_KEY_RELEASE, 0, key_release, &game);
	mlx_loop_hook(game.win.mlx, mlx_main_loop, &game);
	mlx_loop(game.win.mlx);
	return (EXIT_SUCCESS);
}
