/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 10:36:53 by rcappend      #+#    #+#                 */
/*   Updated: 2021/01/18 18:53:05 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	Strlen adjusted to stop counting after finding a specific character.
*/

size_t	ft_strclen(const char *str, int c)
{
	size_t	i;

	if (!*str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == (unsigned char)c && c != 0)
			return (i);
	}
	return (i);
}

/*
**	Memccpy adjusted to copy until it finds the character.
**	If it finds the character, it null terminates destination.
**	It also returns destination instead of NULL.
*/

char	*gnl_memccpy(char *dst, const char *src, int c)
{
	if (!src)
		return (dst);
	while (*src)
	{
		if (*src == (unsigned char)c && c != 0)
		{
			*dst = '\0';
			return ((char *)src);
		}
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (dst);
}

/*
**	Moves memory from end of buffer to beginning,
**	Then makes the rest of the buffer 0.
*/

void	gnl_buffmove(char *dst, const char *src)
{
	size_t	src_len;
	size_t	i;

	if (*src == '\n')
		src++;
	src_len = ft_strclen(src, 0);
	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (i <= src_len)
			dst[i] = src[i];
		else
			dst[i] = 0;
		i++;
	}
}
