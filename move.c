#include "cub.h"

void	move(t_main *Main, t_pl *pl)
{
	if (pl->flg_move_w == 1 && pl->flg_move_s == 0)
		move_frd(Main, pl, pl->ang, 1);
	else if (pl->flg_move_w == 0 && pl->flg_move_s == 1)
		move_frd(Main, pl, pl->ang, -1);
	if (pl->flg_move_a == 1 && pl->flg_move_d == 0)
		move_frd(Main, pl, pl->ang + 90.0, -1);
	else if (pl->flg_move_a == 0 && pl->flg_move_d == 1)
		move_frd(Main, pl, pl->ang + 90.0, 1);
}

void	move_frd(t_main *Main, t_pl *pl, double ang, int speed)
{
	int	x;
	int	y;

	x = (int) pl->x + (int)(4 * speed * cos((ang * PI) / 180));
	y = (int) pl->y + (int)(4 * speed * sin((ang * PI) / 180));
	if (ang > 315.0 || ang <= 45 || (ang >= 135.0 && ang < 225.0))
	{
		y = check_walls_y(Main->map, x, y, speed * sin((ang * PI) / 180));
		x = check_walls_x(Main->map, x, y, speed * cos((ang * PI) / 180));
	}
	else
	{
		x = check_walls_x(Main->map, x, y, speed * cos((ang * PI) / 180));
		y = check_walls_y(Main->map, x, y, speed * sin((ang * PI) / 180));
	}
	pl->y = y;
	pl->x = x;
}

int	check_walls_x(char **map, int x, int y, double one_speed)
{
	int	tmp;
	int	cnt;

	cnt = -1;
	while (++cnt < 4)
	{
		tmp = x - (int)(cnt * one_speed);
		if (map[(y - 2) / 32][(tmp - 4) / 32] != '1' && \
			map[(y - 2) / 32][(tmp + 2) / 32] != '1' && \
			map[(y + 2) / 32][(tmp + 2) / 32] != '1' && \
			map[(y + 2) / 32][(tmp - 4) / 32] != '1')
			return (tmp);
	}
	return (x - (int)(4 * one_speed));
}

int	check_walls_y(char **map, int x, int y, double one_speed)
{
	int	tmp;
	int	cnt;

	cnt = -1;
	while (++cnt < 4)
	{
		tmp = y - (int)(cnt * one_speed);
		if (map[(tmp - 4) / 32][(x - 2) / 32] != '1' && \
			map[(tmp - 4) / 32][(x + 2) / 32] != '1' && \
			map[(tmp + 2) / 32][(x + 2) / 32] != '1' && \
			map[(tmp + 2) / 32][(x - 2) / 32] != '1')
			return (tmp);
	}
	return (y - (int)(4 * one_speed));
}