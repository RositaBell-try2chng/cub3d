#include "cub.h"

static double	find_X_wall(t_main *M, t_pl *pl, int cnt, char *flg)
{

}

static double	find_Y_wall(t_main *M, t_pl *pl, int cnt, char *flg)
{

}

double	cast_right_down(t_main *M, t_pl *pl, int cnt)
{
	double	resX;
	double	resY;
	char	flg_correct_X;
	char	flg_correct_Y;

	flg_correct_X = 1;
	flg_correct_Y = 1;
	resX = find_X_wall(M, pl, cnt, &flg_correct_X);
	resY = find_Y_wall(M, pl, cnt, &flg_correct_Y);
	if ((resX <= resY && flg_correct_X) || !flg_correct_Y)
		return (resX);
	return (resY);
}