#include "cub.h"

static double	check_walls_x(char **map, double x, double y, double one_speed)
{
	double	tmp;
	int	cnt;

	cnt = -1;
	while (++cnt < 3)
	{
		tmp = x - (one_speed * cnt);
		if (get_map_char(map, y - 4, tmp - 4) != '1' && \
			get_map_char(map, y - 4, tmp + 2) != '1' && \
			get_map_char(map, y + 2, tmp + 2) != '1' && \
			get_map_char(map, y + 2, tmp - 4) != '1')
			return (tmp);
	}
	return (x - (one_speed * cnt));
}

static double	check_walls_y(char **map, double x, double y, double one_speed)
{
	double	tmp;
	int	cnt;

	cnt = -1;
	while (++cnt < 3)
	{
		tmp = y - (one_speed * cnt);
		if (get_map_char(map, tmp - 4, x - 4) != '1' && \
			get_map_char(map, tmp - 4, x + 2) != '1' && \
			get_map_char(map, tmp + 2, x + 2) != '1' && \
			get_map_char(map, tmp + 2, x - 4) != '1')
			return (tmp);
	}
	return (y - (one_speed * cnt));
}

static void	move_cnt(t_main *Main, t_pl *pl, double ang, int speed)
{
	double	x;
	double	y;

	x = pl->x + (3 * speed * cos((ang * PI) / 180));
	y = pl->y + (3 * speed * sin((ang * PI) / 180));
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

void    turn(t_pl *pl)
{
	if (pl->flg_trn_r == 1 && pl->flg_trn_l == 0)
		pl->ang += 3;
	else if (pl->flg_trn_r == 0 && pl->flg_trn_l == 1)
		pl->ang -= 3;
	if (pl->ang > 360)
		pl->ang -= 360;
	if (pl->ang < 0)
		pl->ang += 360;
}

void	move(t_main *Main, t_pl *pl)
{
	if (pl->flg_move_w == 1 && pl->flg_move_s == 0)
		move_cnt(Main, pl, pl->ang, 1);
	else if (pl->flg_move_w == 0 && pl->flg_move_s == 1)
		move_cnt(Main, pl, pl->ang, -1);
	if (pl->flg_move_a == 1 && pl->flg_move_d == 0)
		move_cnt(Main, pl, pl->ang + 90.0, -1);
	else if (pl->flg_move_a == 0 && pl->flg_move_d == 1)
		move_cnt(Main, pl, pl->ang + 90.0, 1);
}