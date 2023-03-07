SRCS		= main.c ft_split.c hooks.c move.c raycast.c casts_utils.c \
				cast_horisontal_vertical.c cast_left_down.c cast_left_up.c cast_right_down.c cast_right_up.c

OBJS		= ${SRCS:.c=.o}

HEAD		= cub.h

NAME		= cub3d

MLX			= mlx/

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -O2

LIBS		= -lmlx -framework OpenGL -framework AppKit

%.o:	%.c ${HEAD}
		${CC} ${CFLAGS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
