/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/22 11:13:02 by rcappend      #+#    #+#                 */
/*   Updated: 2021/02/28 12:30:54 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

// fix png leaks or remove
static int		get_image(t_text *tex, void *mlx_ptr)
{
	int		len;
	
	len = ft_strlen(tex->path);
	if (ft_strncmp(tex->path + len - 4, ".png", 4) == 0)
		tex->img = mlx_png_file_to_image(mlx_ptr, tex->path,\
		&tex->width, &tex->height);
	else
		tex->img = mlx_xpm_file_to_image(mlx_ptr, tex->path,\
		&tex->width, &tex->height);
	free(tex->path);
	if (!tex->img)
		return (EXIT_FAILURE);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,\
				&tex->endian);
	return (EXIT_SUCCESS);
}

int				load_textures(t_textures *texts, void *mlx_ptr)
{
	int		error;

	error = get_image(&texts->no_text, mlx_ptr);
	if (!error)
		error = get_image(&texts->ea_text, mlx_ptr);
	if (!error)
		error = get_image(&texts->so_text, mlx_ptr);
	if (!error)
		error = get_image(&texts->we_text, mlx_ptr);
	if (!error)
		error = get_image(&texts->spr_text, mlx_ptr);
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}