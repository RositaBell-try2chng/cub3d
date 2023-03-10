SRCS		= main.c ft_split.c hooks.c raycast.c casts_utils.c \
				cast_horisontal_vertical.c cast_left_down.c cast_left_up.c cast_right_down.c cast_right_up.c \
				draws.c draws_utils.c \
				draw_map.c draw_map_utils.c \
				common_utils.c \
				move.c move_utils.c

OBJS		= ${SRCS:.c=.o}

HEAD		= cub.h

NAME		= cub3d

MLX			= mlx/

LINUX_CC	= clang
MACOS_CC	= cc

RM			= rm -f

# Later: don't repeat yourself, clean this up later
# Later: possible bug: are -framework libs or more like cflags?
MACOS_LIBS = -lmlx -framework OpenGL -framework AppKit
LINUX_LIBS = -Lmlx_linux -lXext -lX11 -lmlx


CC			= \
              	${if ${filter Linux, ${shell uname}}, ${LINUX_CC}} \
              	${if ${filter Darwin, ${shell uname}}, ${MACOS_CC}}

# Later: possible build optimization: add colon to force evaluation
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -O2 \
	${if ${filter Linux, ${shell uname}}, -DCUB_PLATFORM=CUB_PLATFORM_LINUX} \
	${if ${filter Darwin, ${shell uname}}, -DCUB_PLATFORM=CUB_PLATFORM_MACOS}

LIBS = \
	${if ${filter Linux, ${shell uname}}, ${LINUX_LIBS}} \
	${if ${filter Darwin, ${shell uname}}, ${MACOS_LIBS}}

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
