#include "cub.h"

static char	check_walls(char **map, double x, double y)
{
	if (get_map_char(map, y - 2, x - 2) == '1' || \
		get_map_char(map, y - 2, x + 2) == '1' || \
		get_map_char(map, y + 2, x + 2) == '1' || \
		get_map_char(map, y + 2, x - 2) == '1')
		return (1);
	return (0);
}

static void	move_cnt_recursive(t_move *mv, char flg, char step)
{
	double	k;

	if (step == 6)
		return ;
	if (flg == 'y')
	{
		k = mv->pl->y + (mv->speed * sin((mv->ang * PI) / 180));
		if (!check_walls(mv->map, mv->pl->x, k))
			mv->pl->y = k;
		move_cnt_recursive(mv, 'x', step + 1);
	}
	else if (flg == 'x')
	{
		k = mv->pl->x + (mv->speed * cos((mv->ang * PI) / 180));
		if (!check_walls(mv->map, k, mv->pl->y))
			mv->pl->x = k;
		move_cnt_recursive(mv, 'y', step + 1);
	}
}

static void	move_cnt(t_main *Main, t_pl *pl, double ang, int speed)
{
	t_move	mv;

	mv.pl = pl;
	mv.map = Main->map;
	mv.ang = ang;
	mv.speed = speed;
	if (ang > 315.0 || ang <= 45 || (ang >= 135.0 && ang < 225.0))
		move_cnt_recursive(&mv, 'y', 0);
	else
		move_cnt_recursive(&mv, 'x', 0);
}

void	move(t_main *Main, t_pl *pl)
{
	if (pl->flg_move_w == 1 && pl->flg_move_s == 0)
		move_cnt(Main, pl, pl->ang, 1);
	else if (pl->flg_move_w == 0 && pl->flg_move_s == 1)
		move_cnt(Main, pl, pl->ang, -1);
	if (pl->flg_move_a == 1 && pl->flg_move_d == 0)
		move_cnt(Main, pl, pl->ang - 90.0, 1);
	else if (pl->flg_move_a == 0 && pl->flg_move_d == 1)
		move_cnt(Main, pl, pl->ang + 90.0, 1);
}

void	turn(t_pl *pl)
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