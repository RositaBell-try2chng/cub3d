#include "cub.h"

int	define_speed_ang(t_pl *pl, double *p_ang)
{
	int	res_w;
	int	res_d;

	res_w = pl->flg_move_w + pl->flg_move_s;
	res_d = pl->flg_move_d + pl->flg_move_a;
	if (res_w == 0 && res_d == 0)
		return (0);
	if (res_w == 1 || res_w == -1)
	{
		(*p_ang) += 45.0 * res_d * res_w;
		return (res_w);
	}
	(*p_ang) += 90.0;
	return (res_d);
}

void	move(t_main *Main, t_pl *pl)
{
	int		speed;
	double	ang;

	ang = pl->ang;
	speed = define_speed_ang(pl, &ang);
//	if (pl->flg_move_w == 1 && pl->flg_move_s == 0)
//		move_cnt(Main, pl, pl->ang, 1);
//	else if (pl->flg_move_w == 0 && pl->flg_move_s == 1)
//		move_cnt(Main, pl, pl->ang, -1);
//	if (pl->flg_move_a == 1 && pl->flg_move_d == 0)
//		move_cnt(Main, pl, pl->ang - 90.0, 1);
//	else if (pl->flg_move_a == 0 && pl->flg_move_d == 1)
	move_cnt(Main, pl, ang, speed);
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