/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/21 16:53:58 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/25 12:03:40 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

static void		conf_init(t_mlx *win, t_textures *text, \
							t_player *player, t_map *map)
{
	win->res_x = -1;
	win->res_y = -1;
	text->no_text.path = NULL;
	text->ea_text.path = NULL;
	text->so_text.path = NULL;
	text->we_text.path = NULL;
	text->spr_text.path = NULL;
	text->c_col = -1;
	text->f_col = -1;
	map->map = NULL;
	map->sprites = NULL;
	map->width = 0;
	map->height = 0;
	player->x = -1;
	player->dir_x = -2;
}

/*
** this functions parses over the file line by line
** sends first 8 lines to be saved in the conf struct
** next lines are sent to be saved in the map
*/

static void		parse_file(const int fd, t_game *game)
{
	char	*buff;
	int		start;
	int		error;
	int		conf_n;

	start = 1;
	buff = NULL;
	conf_n = 0;
	while (start > 0)
	{
		start = get_next_line(fd, &buff);
		if (start < 0)
			exit_error("GNL Failure");
		if (conf_n <= 8 && *buff != '\0')
			error = save_config(buff, game, &game->textures, &conf_n);
		else if (conf_n == 8 && *buff != '\0')
			conf_n++;
		if (conf_n == 9)
			error = save_map(buff, &game->map, &conf_n);
		free(buff);
		if (error)
			exit_error("Failure parsing file");
	}
}

void			read_file(const char *file_path, t_game *game)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (!fd)
		exit_error("Error opening file");
	conf_init(&game->win, &game->textures, \
				&game->player, &game->map);
	parse_file(fd, game);
	close(fd);
	make_grid(&game->map);
	check_map(game->map, &game->player);
}
