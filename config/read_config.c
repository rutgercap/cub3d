/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rutgercappendijk <rutgercappendijk@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:00:26 by rcappend          #+#    #+#             */
/*   Updated: 2021/05/12 16:20:47 by rutgercappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

static int	save_res(const char *line, t_mlx *win)
{
	while (ft_isspace(*line))
		line++;
	if (!ft_isdigit(*line))
		return (EXIT_FAILURE);
	win->res_x = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	if (!ft_isdigit(*line))
		return (EXIT_FAILURE);
	win->res_y = ft_atoi(line);
	if (win->res_x <= 0 || win->res_y <= 0)
		return (EXIT_FAILURE);
	while (ft_isdigit(*line))
		line++;
	if (*line != '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	save_texture_path(const char *line, char **dest)
{
	int		len;

	while (ft_isspace(*line))
		line++;
	len = ft_strlen(line);
	if (ft_strncmp(line + len - 4, ".png", 4) != 0 && \
		ft_strncmp(line + len - 4, ".xpm", 4) != 0)
		return (EXIT_FAILURE);
	*dest = ft_substr(line, 0, len);
	if (!dest)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	save_color(int *dest, char *line)
{
	if (!ft_isdigit(*line))
		return (EXIT_FAILURE);
	*dest = ft_atoi(line);
	if (*dest > 255)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	save_rgb(char *line, int *dest)
{
	int		r;
	int		g;
	int		b;

	while (ft_isspace(*line))
		line++;
	if (save_color(&r, line))
		return (EXIT_FAILURE);
	while (ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	if (save_color(&g, line))
		return (EXIT_FAILURE);
	while (ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	if (save_color(&b, line))
		return (EXIT_FAILURE);
	while (ft_isdigit(*line))
		line++;
	if (*line != '\0')
		return (EXIT_FAILURE);
	*dest = create_trgb(0, r, g, b);
	return (EXIT_SUCCESS);
}

int	save_config(char *line, t_game *game, t_textures *text, int *conf_n)
{
	int		error;

	error = EXIT_FAILURE;
	if (*conf_n == 8)
		error = EXIT_SUCCESS;
	else if (game->win.res_x == -1 && !ft_strncmp(line, "R ", 2))
		error = save_res(line + 2, &game->win);
	else if (text->no_text.path == NULL && !ft_strncmp(line, "NO ", 3))
		error = save_texture_path(line + 3, &text->no_text.path);
	else if (text->so_text.path == NULL && !ft_strncmp(line, "SO ", 3))
		error = save_texture_path(line + 3, &text->so_text.path);
	else if (text->we_text.path == NULL && !ft_strncmp(line, "WE ", 3))
		error = save_texture_path(line + 3, &text->we_text.path);
	else if (text->ea_text.path == NULL && !ft_strncmp(line, "EA ", 3))
		error = save_texture_path(line + 3, &text->ea_text.path);
	else if (text->spr_text.path == NULL && !ft_strncmp(line, "S ", 2))
		error = save_texture_path(line + 2, &text->spr_text.path);
	else if (text->f_col == -1 && !ft_strncmp(line, "F ", 2))
		error = save_rgb(line + 2, &text->f_col);
	else if (text->c_col == -1 && !ft_strncmp(line, "C ", 2))
		error = save_rgb(line + 2, &text->c_col);
	if (error == EXIT_SUCCESS)
		*conf_n += 1;
	return (error);
}
