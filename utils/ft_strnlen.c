/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnlen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 10:11:12 by rcappend      #+#    #+#                 */
/*   Updated: 2020/12/07 11:25:58 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (*s && maxlen > 0)
	{
		s++;
		i++;
		maxlen--;
	}
	return (i);
}
