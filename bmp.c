/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rutgercappendijk <rutgercappendijk@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 15:00:22 by rutgercappe   #+#    #+#                 */
/*   Updated: 2021/05/26 10:28:35 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	header_size(int x, int y)
{
	if (3 * x % 4 != 0)
		x = x + 4 - ((3 * x) % 4);
	return (54 + (3 * x * y));
}

static int	get_color(t_image img, const int x, const int y)
{
	char	*dest;
	int		color;
	int		rgb;

	dest = img.addr + (y * img.line_len + \
				x * (img.bpp) / 8);
	color = *(int *)dest;
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static void	write_bmp_header(uint8_t *buff, const int res_x, \
							const int res_y, const size_t filesize)
{
	*((uint8_t *)&buff[0]) = (uint8_t)0x42;
	*((uint8_t *)&buff[1]) = (uint8_t)0x4D;
	*((uint32_t *)&buff[2]) = (uint32_t)filesize;
	*((uint32_t *)&buff[10]) = (uint32_t)54;
	*((uint32_t *)&buff[14]) = (uint32_t)0x28;
	*((uint32_t *)&buff[18]) = (uint32_t)res_x;
	*((uint32_t *)&buff[22]) = (uint32_t)res_y;
	*((uint16_t *)&buff[26]) = (uint16_t)0x01;
	*((uint16_t *)&buff[28]) = (uint16_t)0x18;
}

static void	write_bmp_img(uint8_t *buff, t_image *img, \
							const int res_x, int res_y)
{
	uint32_t	i;
	int			index_x;
	int			color;

	i = HEADERSIZE;
	res_y--;
	while (res_y >= 0)
	{
		index_x = 0;
		while (index_x < res_x)
		{
			color = get_color(*img, index_x, res_y);
			buff[i + 0] = color;
			buff[i + 1] = color >> 8;
			buff[i + 2] = color >> 16;
			i += 3;
			index_x++;
		}
		if ((res_x * 3) % 4 != 0)
			i += 4 - (res_x * 3) % 4;
		res_y--;
	}
}

void	save_bmp(t_game *game)
{
	int		fd;
	uint8_t	*buff;
	size_t	filesize;
	t_mlx	*win;

	win = &game->win;
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777 | O_TRUNC);
	if (fd < 0)
		exit_error("Failed to create bmp");
	generate_image(game, &game->img_1);
	filesize = header_size(win->res_x, win->res_y);
	buff = ft_calloc(filesize, 1);
	write_bmp_header(buff, win->res_x, win->res_y, filesize);
	write_bmp_img(buff, &game->img_1, win->res_x, win->res_y);
	if (!buff)
		exit_error("Malloc failure");
	if (write(fd, buff, filesize) < 0)
		exit_error("Write failure");
	if (close(fd) < 0)
		exit_error("File closing failure");
	free(buff);
}
