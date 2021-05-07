/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutgercappendijk <rutgercappendijk@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:13:38 by rcappend          #+#    #+#             */
/*   Updated: 2021/05/07 10:41:51 by rutgercappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "utils/utils.h"
# include "cub3d.h"

# define WALL 49
# define FLOOR 48
# define OPEN 32

typedef struct s_pos
{
	int			x;
	int			y;
	char		dir;
}				t_pos;

int				save_config(const char *line, t_game *game, \
				t_textures *text, int *conf_n);

int				save_map(const char *line, t_map *map, int *conf_n);

void			north_east_to_dir(t_player *player);

void			south_west_to_dir(t_player *player);

void			make_grid(t_map *map);

void			check_map(const t_map map, t_player *player);

#endif
