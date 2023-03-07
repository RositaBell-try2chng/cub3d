#include "cub.h"

static double	find_X_wall(t_main *M, t_pl *pl, int cnt, char *flg)
{
	double	newX;
	double	newY;
	char	flg_wall;
	double	ang;

	flg_wall = 0;
	ang = 90.0 - fmod(pl->rays_ang[cnt], 90.0);
	newX = (double)(((pl->x / 32) + 1) * 32.0);
	while (!flg_wall)
	{
		newY = pl->y - (newX - pl->x) * tan(ang * PI / 180.0);
		if (!check_correct(M, newX, newY, flg))
			return (-1);
		else if (check_wall(M, newX, newY))
			flg_wall = 1;
		else
			newX += 32.0;
	}
	return (sqrt(pow(newY - pl->y, 2) + pow(newX - pl->x, 2)));
}

static double	find_Y_wall(t_main *M, t_pl *pl, int cnt, char *flg)
{
	double	newX;
	double	newY;
	char	flg_wall;
	double	ang;

	flg_wall = 0;
	ang = fmod(pl->rays_ang[cnt], 90.0);
	newY = (double)(((pl->y / 32) * 32.0) - 0.0001);
	while (!flg_wall)
	{
		newX = pl->x + (pl->y - newY) * tan(ang * PI / 180.0);
		if (!check_correct(M, newX, newY, flg))
			return (-1);
		else if (check_wall(M, newX, newY))
			flg_wall = 1;
		else
			newY -= 32.0;
	}
	return (sqrt(pow(newY - pl->y, 2) + pow(newX - pl->x, 2)));
}

double	cast_right_up(t_main *M, t_pl *pl, int cnt)
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
	{
		pl->wall_color[cnt] = WALL_W;
		return (resX);
	}
	pl->wall_color[cnt] = WALL_S;
	return (resY);
}