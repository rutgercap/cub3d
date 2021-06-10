/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 10:39:19 by rcappend      #+#    #+#                 */
/*   Updated: 2021/05/28 08:58:49 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

size_t	ft_strclen(const char *str, int c);

char	*ft_strchr(const char *s, int c);

char	*gnl_memccpy(char *dst, const char *src, int c);

void	gnl_buffmove(char *dst, const char *src);

int		get_next_line(int fd, char **line);

#endif
