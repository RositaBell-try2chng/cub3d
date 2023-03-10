#include "cub.h"

static double	find_X_wall(t_main *M, t_hit *hit, char *flg)
{
	double	newX;
	double	newY;
	char	flg_wall;
	double	ang;

	flg_wall = 0;
	ang = 90.0 - fmod(hit->ang, 90.0);
	newX = (double)(((hit->pl_x / 32) + 1) * 32.0);
	while (!flg_wall)
	{
		newY = hit->pl_y - (newX - hit->pl_x) * tan(ang * PI / 180.0);
		if (!check_correct(M, newX, newY, flg))
			return (-1);
		else if (check_wall(M, newX, newY))
			flg_wall = 1;
		else
			newX += 32.0;
	}
	hit->X_y = newY;
	return (sqrt(pow(newY - hit->pl_y, 2) + pow(newX - hit->pl_x, 2)));
}

static double	find_Y_wall(t_main *M, t_hit *hit, char *flg)
{
	double	newX;
	double	newY;
	char	flg_wall;
	double	ang;

	flg_wall = 0;
	ang = fmod(hit->ang, 90.0);
	newY = (double)(((hit->pl_y / 32) * 32.0) - 0.000001);
	while (!flg_wall)
	{
		newX = hit->pl_x + (hit->pl_y - newY) * tan(ang * PI / 180.0);
		if (!check_correct(M, newX, newY, flg))
			return (-1);
		else if (check_wall(M, newX, newY))
			flg_wall = 1;
		else
			newY -= 32.0;
	}
	hit->Y_x = newX;
	return (sqrt(pow(newY - hit->pl_y, 2) + pow(newX - hit->pl_x, 2)));
}

double	cast_right_up(t_main *M, t_hit *hit)
{
	double	resX;
	double	resY;
	char	flg_correct_X;
	char	flg_correct_Y;

	flg_correct_X = 1;
	flg_correct_Y = 1;
	resX = find_X_wall(M, hit, &flg_correct_X);
	resY = find_Y_wall(M, hit, &flg_correct_Y);
	if (!flg_correct_X && !flg_correct_Y)
		exit(printf("incorrect flags\n"));
	if ((resX <= resY && flg_correct_X) || !flg_correct_Y)
	{
		hit->flg_wall = 'X';
		hit->side = &M->mp->wall_W;
		return (resX);
	}
	hit->flg_wall = 'Y';
	hit->side = &M->mp->wall_S;
	return (resY);
}