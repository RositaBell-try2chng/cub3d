#include "cub.h"

void	move(t_main *Main, t_pl *pl)
{
	int		speed;
	double	ang;

	ang = pl->ang;
	speed = define_speed_ang(pl, &ang);
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