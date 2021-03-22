# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rcappend <rcappend@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/18 13:39:03 by rcappend      #+#    #+#                  #
#    Updated: 2021/03/14 13:42:33 by rcappend      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		=	main.c \
				./utils/ft_strchr.c ./utils/ft_strlen.c ./utils/ft_atoi.c \
				./utils/ft_isdigit.c ./utils/ft_strncmp.c ./utils/ft_substr.c \
				./utils/ft_calloc.c ./utils/ft_isspace.c ./utils/ft_memcpy.c \
				./utils/ft_bzero.c ./utils/create_trgb.c ./utils/ft_strcpy.c \
				./utils/ft_memset.c \
				./gnl/get_next_line_utils.c ./gnl/get_next_line.c \
				./config/read_config.c ./config/file_parser.c \
				./config/check_map.c ./config/config_utils.c \
				./config/make_map.c ./config/load_textures.c \
				./engine/init.c ./engine/draw_utils.c \
				./engine/render_next_frame.c ./engine/key_hooks.c \
				./engine/raycasting.c ./engine/draw_room.c \
				./engine/draw_sprites.c ./engine/calc_sprite.c \
				./engine/sprite_utils.c
OBJS		=	$(SRCS:.c=.o)

LIBS		=	-Lmlx -lmlx -framework OpenGL -framework AppKit -lm

MLX			=	libmlx.dylib

CC			=	gcc

CFLAGS		= 	-Wall -Wextra -fsanitize=address -g3 -I. # clean up

all:		$(NAME)
$(NAME):	$(MLX) $(OBJS)
			gcc ${CFLAGS} ${LIBS} ${OBJS}  -o ${NAME}

$(MLX):
	@$(MAKE) -C mlx
	mv mlx/$(MLX) .

test: all
	./$(NAME) maps/normal.cub

simple: all
	./$(NAME) maps/simple.cub

sprite: all
	./$(NAME) maps/sprites.cub

dtest: all
	lldb cub3d maps/normal.cub

dsimple: all
	lldb cub3d maps/simple.cub

dsprite: all
	lldb cub3d maps/sprites.cub

clean:
	@$(MAKE) -C mlx clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(MLX)

re:	fclean all

phony:
	all clean fclean re libft