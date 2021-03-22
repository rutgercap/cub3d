/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_sprite.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/12 12:48:07 by rcappend      #+#    #+#                 */
/*   Updated: 2021/03/15 13:11:54 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void		set_sprite_distance(t_sprite **head, const int pos_x, \
								const int pos_y)
{
	t_sprite	*current;

	current = *head;
	while (current != NULL)
	{
		current->distance = ((pos_x - current->x) * (pos_x - current->x) + \
							(pos_y - current->y) * (pos_y - current->y));
		current = current->next;
	}
	merge_sort_sprites(head);
}

void		set_transform(t_draw_spr *dst, const t_sprite sprite, \
							const t_player player, const int w)
{
	double		inv_det;

	inv_det = 1.0 / ((player.plane_x * player.dir_y) - \
					(player.dir_x * player.plane_y));
	dst->trans_x = inv_det * (player.dir_y * sprite.x - \
								player.dir_x * sprite.y);
	dst->trans_y = inv_det * (-player.plane_y * sprite.x + \
								player.plane_x * sprite.y);
	dst->sprite_x = (int)(w / 2.0) * (1.0 + dst->trans_x / dst->trans_y);
}

void 		set_draw_y(t_draw *draw, const int res_y, const double trans_y)
{
	draw->length = (int)fabs(res_y / trans_y);
	draw->draw_start = -draw->length / 2 + res_y / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_stop = draw->length / 2 + res_y / 2;
	if (draw->draw_stop >= res_y)
		draw->draw_stop = res_y - 1;
}

void		set_draw_x(t_draw *draw, const t_mlx win, \
						const double trans_y, const int sprite_x)
{
	draw->length = (int)fabs(win.res_y / trans_y);
	draw->draw_start = -draw->length / 2 + sprite_x;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_stop = draw->length / 2 + sprite_x;
	if (draw->draw_stop >= win.res_x)
		draw->draw_stop = win.res_x;
}
