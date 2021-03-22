/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_room.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/12 12:38:22 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/22 12:51:21 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static t_draw	set_draw_wall(const t_ray ray, const int res_y, const int x)
{
	t_draw	draw;
	
	draw.x = x;
	if (ray.distance == 0)
		draw.length = res_y;
	else
		draw.length = (int)(res_y / ray.distance);
	draw.draw_start = -draw.length / 2 + res_y / 2;
	if (draw.draw_start < 0)
		draw.draw_start = 0;
	draw.draw_stop = draw.length / 2 + res_y / 2;
	if (draw.draw_stop >= res_y)
		draw.draw_stop = res_y - 1;
	return (draw);
}

static void		draw_ceiling_floor(t_image *img, const t_textures texts, \
									const t_draw draw, const int res_y)
{
	int		y;

	y = 1;
	while (y < draw.draw_start)
	{
		my_mlx_pixel_put(img, draw.x, y, texts.c_col);
		y++;
	}
	y = draw.draw_stop;
	while (y < res_y - 1)
	{
		my_mlx_pixel_put(img, draw.x, y, texts.f_col);
		y++;
	}
}

static t_text	get_text(const t_textures texts, const int side, \
							const double dir_x, const double dir_y)
{
	if (side)
		if (dir_y < 0)
			return (texts.no_text);
		else
			return (texts.so_text);
	else
		if (dir_x < 0)
			return (texts.we_text);
		else
			return (texts.ea_text);
}

static int		get_tex_x(const t_text text, const t_game game, \
							const t_ray ray)
{
	double	wall_x;
	int		tex_x;

	if (ray.side == 0)
		wall_x = game.player.y + ray.distance * ray.raydir_y;
	else
		wall_x = game.player.x + ray.distance * ray.raydir_x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)text.width);
	if (ray.side == 0 && ray.raydir_x > 0)
		tex_x = text.width - tex_x - 1;
	if (ray.side == 1 && ray.raydir_y < 0)
		tex_x = text.width - tex_x - 1;
	return (tex_x);
}

void			draw_room(t_image *img, const t_game game, \
							const t_ray ray)
{
	t_draw			draw;
	t_text			text;
	int				y;
	int				tex_x;
	int				tex_y;
	double			step;
	char			*dest;
	unsigned int	color;
	double			tex_pos;

	draw = set_draw_wall(ray, game.win.res_y, ray.x);
	draw_ceiling_floor(img, game.textures, draw, game.win.res_y);
	text = get_text(game.textures, ray.side, ray.raydir_x, ray.raydir_y);
	tex_x = get_tex_x(text, game, ray);
	step = 1.0 * text.height / draw.length;
	tex_pos = (draw.draw_start - game.win.res_y / 2 + draw.length / 2) * step;
	y = draw.draw_start;
	while (y < draw.draw_stop)
	{
		tex_y = (int)tex_pos & (text.height - 1);
		tex_pos += step;
		dest = text.addr + (tex_y * text.line_len + tex_x * (text.bpp / 8));
		color = *(unsigned int*)dest;
		my_mlx_pixel_put(img, ray.x, y, color);
		y++;
	}
}
