/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   engine.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/18 09:37:53 by rcappend      #+#    #+#                 */
/*   Updated: 2021/05/28 10:45:27 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "../mlx/mlx.h"
# include "../cub3d.h"
# include <math.h>

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESCAPE 53

# define HEADER_SIZE 21

/*
** structs needed for raycasting and drawing
*/

typedef struct s_ray {
	int		x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	distance;
	int		side;
}	t_ray;

typedef struct s_draw {
	int	x;
	int	length;
	int	draw_start;
	int	draw_stop;
}	t_draw;

typedef struct s_wall {
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}	t_wall;

typedef struct s_draw_sprite {
	t_draw	draw_x;
	t_draw	draw_y;
	t_text	text;
	int		tex_x;
	int		tex_y;
	double	trans_x;
	double	trans_y;
	int		sprite_x;
}	t_draw_spr;

void	my_mlx_pixel_put(t_image *img, int x, int y, int color);

void	move_left_right(t_player *player, const int key, const t_map map);

void	move_forward_backward(t_player *player, const int key, const t_map map);

void	turn_right_left(t_player *player, const int key);

void	raycaster(t_ray *ray, const t_game game, \
		int *sprites, double *distance);

void	draw_room(t_image *img, const t_game game, const t_ray ray);

void	draw_sprites(t_image *img, t_sprite **head, \
		const t_game game, double *z_buffer);

void	merge_sort_sprites(t_sprite **head_ref);

void	set_transform(t_draw_spr *dst, const t_sprite sprite, \
		const t_player player, const int w);

void	set_sprite_distance(t_sprite **head, \
		const double pos_x, const double pos_y);

void	set_draw_y(t_draw *draw, const int res_y, const double trans_y);

void	set_draw_x(t_draw *draw, const t_mlx win, \
		const double trans_y, const int sprite_x);

#endif