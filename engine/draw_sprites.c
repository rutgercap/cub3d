/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 10:18:26 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/15 13:06:00 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/*
**	"set_tex" function is added to avoid hardcoding the only sprite texture
**	once more sprites are added to the game they can easily be added here.
*/

static void	set_text(t_text *text, const char type, const t_textures texts)
{
	if (type == '2')
		*text = texts.spr_text;
}

static void	draw_sprite_y(t_image *img, t_draw_spr dr_sp, \
							const int res_y, const int x)
{
	t_text			text;
	t_draw			draw_y;
	t_draw			draw_x;
	char			*dest;
	unsigned int	color;
	int				tex_y;
	int				d;

	text = dr_sp.text;
	draw_y = dr_sp.draw_y;
	draw_x = dr_sp.draw_x;
	while (draw_y.draw_start < draw_y.draw_stop)
	{ 
		d = draw_y.draw_start * 256 - res_y * 128 + draw_y.length * 128;
		tex_y = ((d * text.height) / draw_y.length) / 256;
		dest = text.addr + (tex_y * text.line_len + \
				dr_sp.tex_x * (text.bpp / 8));
		color = *(unsigned int*)dest;
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(img, x, draw_y.draw_start, color);
		draw_y.draw_start++;
	}
}

void		draw_sprites(t_image *img, const t_game game, double *z_buffer)
{
	t_sprite		*current;
	t_draw_spr		dr_sp;
	int				x;

	current = game.map.sprites;
	set_sprite_distance(&current, game.player.x, game.player.y);
	while (current != NULL)
	{
		set_text(&dr_sp.text, current->type, game.textures);
		set_transform(&dr_sp, *current, game.player, game.win.res_x);
		set_draw_y(&dr_sp.draw_y, game.win.res_y, dr_sp.trans_y);
		set_draw_x(&dr_sp.draw_x, game.win, dr_sp.trans_y, dr_sp.sprite_x);
		x = dr_sp.draw_x.draw_start;
		while (x < dr_sp.draw_x.draw_stop)
		{
			dr_sp.tex_x = (int)(256 * (x - (-dr_sp.draw_x.length / 2 + \
				dr_sp.sprite_x)) * dr_sp.text.width / dr_sp.draw_x.length) / 256;
			if (dr_sp.trans_y > 0 && x > 0 && x < game.win.res_x && \
					dr_sp.trans_y < z_buffer[x])
				draw_sprite_y(img, dr_sp, game.win.res_y, x);
			x++;
		}
		current = current->next;
	}
}
