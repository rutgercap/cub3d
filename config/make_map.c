/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/22 07:59:52 by rcappend      #+#    #+#                 */
/*   Updated: 2021/04/26 15:53:38 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void	make_grid(t_map *map)
{
	char	**temp;
	int		i;

	temp = ft_calloc(map->height + 1, sizeof(char *));
	if (!temp)
		exit_error("Error saving map");
	i = 0;
	while (i < map->height)
	{
		temp[i] = ft_calloc(map->width + 1, 1);
		if (!temp[i])
			exit_error("Error saving map");
		i++;
	}
	i--;
	while (i >= 0)
	{
		ft_memset(temp[i], ' ', map->width);
		ft_strcpy(temp[i], map->map[i], map->width + 1);
		free(map->map[i]);
		i--;
	}
	free(map->map);
	map->map = temp;
}

static char	**add_to_map(char **map, const char *line, int n)
{
	char	**temp;

	temp = ft_calloc(sizeof(char *), n + 2);
	if (!temp)
		return (NULL);
	temp[n] = ft_substr(line, 0, ft_strlen(line));
	if (!temp[n])
	{
		free(temp);
		return (NULL);
	}
	while (n > 0)
	{
		n--;
		temp[n] = map[n];
	}
	return (temp);
}

int	save_map(const char *line, t_map *map, int *conf_n)
{
	char	**temp;
	int		i;
	int		line_len;

	if (*line == '\0')
	{
		*conf_n += 1;
		return (EXIT_SUCCESS);
	}
	i = 0;
	temp = NULL;
	if (map->map)
		while (map->map[i])
			i++;
	temp = add_to_map(map->map, line, i);
	if (!temp)
		exit_error("Error saving map");
	if (map->map)
		free(map->map);
	map->map = temp;
	line_len = ft_strlen(line);
	if (line_len > map->width)
		map->width = line_len;
	map->height += 1;
	return (EXIT_SUCCESS);
}
