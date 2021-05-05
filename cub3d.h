/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 18:15:11 by rcappend      #+#    #+#                 */
/*   Updated: 2021/04/30 13:03:35 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CUB3D_H
#	define CUB3D_H

#include "utils/utils.h"
#include <mlx/mlx.h>
#include <stdio.h>

# define FLOOR 48
# define WALL 49
# define SPRITE 50
# define OPEN 32

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
// # define X_EVENT_MOUSE_PRESS	4
// # define X_EVENT_MOUSE_RELEASE	5
// # define X_EVENT_MOUSE_MOVE		6
// # define X_EVENT_EXIT			17

/*
**  sprite list struct
*/

typedef struct 			s_sprite {
	double              distance;
    double				x;
	double				y;
	char				type;
	struct s_sprite		*next;
}						t_sprite;

/*
**	mlx, image and texture structs
*/

typedef struct  s_mlx {
    void        *mlx;
    void        *win;
	int			res_x;
	int			res_y;
}               t_mlx;

typedef struct  s_image {
    void        *img;
    char        *addr;
    int         bpp;
    int         line_len;
    int         endian;
}               t_image;

typedef struct  s_text {
    char		*path;
    void        *img;
    char        *addr;
    int         bpp;
    int         line_len;
    int         endian;
    int         height;
    int         width;
}               t_text;

typedef struct s_textures {
    t_text      no_text;
    t_text      ea_text;
    t_text      so_text;
    t_text      we_text;
	t_text		spr_text;
	int			f_col;
	int			c_col;
}				t_textures;

/*
**	structs used for game stats like the map and player attributes
*/

typedef struct	s_map {
	t_sprite	*sprites;	
	char		**map;
	int			width;
	int			height;
}				t_map;

typedef struct  s_player {
    double      x;
    double      y;
    double      dir_x;
    double      dir_y;
    double      plane_x;
    double      plane_y;
    double      move_speed;
    double      rot_speed;
}               t_player;

typedef struct	s_game
{
	t_bool		save;
	t_textures	textures;
	t_mlx		win;
    t_image     img_1;
    t_image     img_2;
	t_map		map;
	t_player	player;
    int         frame_counter;
    int			move;
    int			strafe;
    int         rotate;
}				t_game;

void	init_mlx(t_game *game);

int		xy_to_map(const int x, const int y, const t_map map);

void	save_sprites(t_sprite **sprite, t_map map);

int		exit_error(char const *str);

void	read_file(const char *file_path, t_game *game);

void	load_textures(t_textures *texts, void *mlx_ptr);

int		key_press(const int keycode, t_game *game);

int		key_release(const int keycode, t_game *game);

int		mlx_main_loop(t_game *game);

void	set_struct_values(t_game *game);

#	endif