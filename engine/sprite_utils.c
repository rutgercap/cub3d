/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 12:37:47 by rcappend      #+#    #+#                 */
/*   Updated: 2021/04/27 11:14:42 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	front_back_split(t_sprite *source, t_sprite **frontref, \
							t_sprite **backref)
{
	t_sprite	*fast;
	t_sprite	*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontref = source;
	*backref = slow->next;
	slow->next = NULL;
}

static t_sprite	*sorted_merge(t_sprite *a, t_sprite *b)
{
	t_sprite	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->distance >= b->distance)
	{
		result = a;
		result->next = sorted_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next);
	}
	return (result);
}

void	merge_sort_sprites(t_sprite **head_ref)
{
	t_sprite	*head;
	t_sprite	*a;
	t_sprite	*b;

	head = *head_ref;
	if (head == NULL || head->next == NULL)
		return ;
	front_back_split(head, &a, &b);
	merge_sort_sprites(&a);
	merge_sort_sprites(&b);
	*head_ref = sorted_merge(a, b);
}

static void	add_sprite_front(t_sprite **head, const double x, \
						const double y, const char type)
{
	t_sprite	*new;

	new = (t_sprite *) malloc(sizeof(t_sprite));
	if (!new)
		exit_error("Error saving sprites");
	new->x = x;
	new->y = y;
	new->type = type;
	new->next = *head;
	*head = new;
}

void	save_sprites(t_sprite **sprite, t_map map)
{
	t_sprite	*head;
	char		type;
	int			x;
	int			y;

	head = NULL;
	y = map.height;
	while (y > 0)
	{
		x = map.width;
		while (x > 0)
		{
			type = xy_to_map(x, y, map);
			if (type == SPRITE)
				add_sprite_front(&head, x + 0.5, y + 0.5, type);
			x--;
		}
		y--;
	}
	*sprite = head;
}
