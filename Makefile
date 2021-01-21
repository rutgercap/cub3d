# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rcappend <rcappend@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/18 13:39:03 by rcappend      #+#    #+#                  #
#    Updated: 2021/01/19 10:28:36 by rcappend      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS		=	main.c \
				./engine/cubed.c \
				./utils/ft_strchr.c ./utils/ft_strlen.c\
				./gnl/get_next_line_utils.c ./gnl/get_next_line.c
OBJS		=	$(SRCS:.c=.o)

LIBS		=	-Lmlx -lmlx -framework OpenGL -framework AppKit -lm

MLX			=	libmlx.dylib

CC			=	gcc

CFLAGS		= 	-Wall -Wextra -Werror -g3 -I. # clean up

all:		$(NAME)
$(NAME):	$(LIBFT) $(MLX) $(OBJS)
			gcc ${CFLAGS} ${LIBS} ${OBJS}  -o ${NAME}

$(MLX):
	@$(MAKE) -C mlx
	mv mlx/$(MLX) .

test: all
	./$(NAME)

clean:
	@$(MAKE) -C mlx clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(MLX)

re:	fclean all

phony:
	all clean fclean re libft