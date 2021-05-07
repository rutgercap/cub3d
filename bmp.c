
#include "cub3d.h"

static void	write_int(unsigned char *dst, const int value)
{
	dst[0] = (unsigned char)(value);
	dst[1] = (unsigned char)(value >> 8);
	dst[2] = (unsigned char)(value >> 16);
	dst[3] = (unsigned char)(value >> 24);
}

static void write_bmp_header(const int fd, const int size, \
							const int res_x, const int res_y)
{
	unsigned char	header[54];
	int				ret;

	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	write_int(header + 2, size);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	write_int(header + 18, res_x);
	write_int(header + 22, res_y);
	header[27] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	ret = write(fd, header, 54);
	if (ret < 0)
		exit_error("Write error");
}

static int	get_color(t_mlx *win, t_image img, const int x, const int y)
{
	int	rgb;
	int	color;

	color = *(int *)(img.addr + \
					(4 * win->res_x * (win->res_y - 1 - y)) + \
					(4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static void	write_bmp_img(const int fd, t_mlx *win, t_image img, const int loc)
{
	unsigned char	zero[3];
	int				i;
	int				j;
	int				color;
	int				ret;

	ft_bzero(zero, 3);
	i = 0;
	while (i < win->res_x)
	{
		j = 0;
		while (j < win->res_y)
		{
			color = get_color(win, img, j, i);
			ret = write(fd, &color, 3);
			if (loc > 0 && ret >= 0)
				ret = write(fd, &zero, loc);
			if (ret < 0)
				exit_error("Write error");
			j++;
		}
		i++;
	}
}

void	save_bmp(t_game *game)
{
	int		fd;
	int		filesize;
	int		loc;
	t_mlx	*win;
	
	win = &game->win;
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777 | O_TRUNC);
	if (fd < 0)
		exit_error("Failed to create bmp");
	generate_image(game, &game->img_1);
	loc = (4 - (win->res_x * 3) % 4) % 4;
	filesize = 54 + (3 * (win->res_x + loc) * win->res_y);
	write_bmp_header(fd, filesize, win->res_x, win->res_y);
	write_bmp_img(fd, &game->win, game->img_1, loc);
	close(fd);
}
