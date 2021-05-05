/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 10:26:46 by rcappend      #+#    #+#                 */
/*   Updated: 2021/04/29 11:12:44 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ret_check(int ret, char **line)
{
	if (ret == -1)
	{
		free(*line);
		return (ret);
	}
	return (ret);
}

int	gnl_strjoin(char **line, char *buff)
{
	char	*new;
	char	*index;
	char	*newl;

	if (ft_strclen(buff, 0) == 0)
		return (0);
	new = (char *)malloc(ft_strclen(buff, '\n') + ft_strclen(*line, 0) + 1);
	if (!new)
		return (-1);
	index = gnl_memccpy(new, *line, 0);
	index = gnl_memccpy(index, buff, '\n');
	free(*line);
	*line = new;
	newl = ft_strchr(buff, '\n');
	gnl_buffmove(buff, index);
	if (!newl)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char		buff[BUFFER_SIZE + 1];
	int				bytes;
	int				ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = (char *)malloc(1);
	if (!*line)
		return (-1);
	*line[0] = '\0';
	ret = gnl_strjoin(line, buff);
	if (ret)
		return (ret_check(ret, line));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (-1);
		ret = gnl_strjoin(line, buff);
		if (ret)
			return (ret_check(ret, line));
	}
	return (0);
}
