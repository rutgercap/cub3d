/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 18:13:38 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/08 12:41:47 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

#include <fcntl.h>
#include "cub3d.h"
#include "gnl/get_next_line.h"
#include "utils/utils.h"

int			save_config(const char *line, t_game *game, \
			t_textures *text, int *conf_n);

int			save_map(const char *line, t_map *map, int *conf_n);

int			make_grid(t_map *map);

int			check_map(const t_map map, t_player *player);

int			ascii_to_dir(t_player *player);

#endif
