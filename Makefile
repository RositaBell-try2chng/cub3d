COMMON_SRCS	= main.c raycast.c casts_utils.c \
              cast_horisontal_vertical.c cast_left_down.c cast_left_up.c cast_right_down.c cast_right_up.c \
              draws_utils.c \
              common_utils.c \
              move.c move_utils.c \
              game_play.c \
			$(addprefix parser/, \
				cub_parser.c \
				write_syscall.c \
				map.c \
				map_left_right_check.c \
				read.c \
				color.c \
				color_2.c \
				color_3.c \
				number.c \
				lines.c \
				chars.c \
				mem.c \
				arrayz.c \
				error.c \
				fd.c \
				line_parse.c \
				) \


SRCS_NO_BON	= ${COMMON_SRCS} draws.c init.c hooks.c

SRCS_BON	= ${COMMON_SRCS}	draws_bonus.c init_bonus.c hooks_bonus.c \
								draw_map_bonus.c draw_map_utils_bonus.c	\
								music_bonus.c

OBJS		= ${SRCS_NO_BON:.c=.o}

OBJS_BON	= ${SRCS_BON:.c=.o}

HEAD		= cub.h

NAME		= cub3D

NAME_BON	= cub3D_bonus

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
	${if ${filter Darwin, ${shell uname}}, -DCUB_PLATFORM=CUB_PLATFORM_MACOS} \

LIBS = \
	${if ${filter Linux, ${shell uname}}, ${LINUX_LIBS}} \
	${if ${filter Darwin, ${shell uname}}, ${MACOS_LIBS}}

# Fix me: switch on platform to use -Imlx, -Imlx_linux or none at all
%.o:	%.c ${HEAD} ${HEAD_BON}
		${CC} -Imlx ${CFLAGS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${NAME}

bonus:			${NAME_BON}

${NAME_BON}:	${OBJS_BON}
				${CC} ${CFLAGS} ${OBJS_BON} ${LIBS} -o ${NAME_BON}

clean_m:
				${RM} ${OBJS}

clean_b:
				${RM} ${OBJS_BON}

clean:		clean_m clean_b

fclean_m:	clean_m
			${RM} ${NAME}

fclean_b:	clean_b
			${RM} ${NAME_BON}

fclean:		clean_m clean_b
			${RM} ${NAME}
			${RM} ${NAME_BON}

re_b:		fclean_b bonus

re:			fclean_m fclean_b all

.PHONY:		all clean_m clean_b clean fclean_m fclean_b fclean re_b re bonus
