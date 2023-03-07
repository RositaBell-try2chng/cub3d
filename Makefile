SRCS		= main.c ft_split.c hooks.c move.c raycast.c casts_utils.c \
				cast_horisontal_vertical.c cast_left_down.c cast_left_up.c cast_right_down.c cast_right_up.c

OBJS		= ${SRCS:.c=.o}

HEAD		= cub.h

NAME		= cub3d

MLX			= mlx/

CC			= clang

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -O2

# MACOS_FLAGS = -lmlx -framework OpenGL -framework AppKit
# 
# LINUX_FLAGS = 
# 
# PLATFORM_FLAGS = \
# 	$(if $(filter Linux, $(shell uname)), $(LINUX_FLAGS)) \
# 	$(if $(filter Darwin, $(shell uname)), $(MACOS_FLAGS))

LIBS		= -Lmlx_linux -lXext -lX11 -lmlx

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
