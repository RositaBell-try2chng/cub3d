#include "cub.h"

double	cast_horisontal(t_main *M, t_pl *pl, int cnt, double ang)
{
	int		sign;
	double	newX;

	sign = 1;
	pl->wall_color[cnt] = WALL_W;
	if (ang == 180.0)
	{
		sign = -1;
		pl->wall_color[cnt] = WALL_E;
	}
	newX = pl->x + 32.0 * sign;
	while (newX >= 0.0 && (int)newX / 32 < M->map_W[pl->y / 32])
	{
		if (M->map[pl->y / 32][(int)newX / 32] == '1')
			break;
		newX += 32.0 * sign;
	}
	newX = floor(newX / 32.0) * 32.0;
	if (sign == -1)
		newX += 32.0;
	return (fabs(newX - pl->x));
}

double	cast_vertical(t_main *M, t_pl *pl, int cnt, double ang)
{
	int		sign;
	double	newY;

	sign = 1;
	pl->wall_color[cnt] = WALL_N;
	if (ang == 270.0)
	{
		sign = -1;
		pl->wall_color[cnt] = WALL_S;
	}
	newY = pl->y + 32.0 * sign;
	while (newY >= 0 && (int)newY < M->map_H)
	{
		if (M->map[(int)newY / 32][pl->x / 32] == '1')
			break;
		newY += 32.0 + sign;
	}
	newY = floor(newY / 32.0) * 32.0;
	if (sign == -1)
		newY += 32;
	return (fabs(newY - pl->Y));
}

double	cast_up(t_main *M, t_pl *pl, int cnt, double ang)
{
	int		signX;
	double	newY;
	double	newX;

	signX = 1;
	if (M->pl->rays_ang[cnt] > 180.0 && M->pl->rays_ang[cnt] < 270.0)
		signX = -1;
	else if (M->pl->rays_ang[cnt] == 270.0)
		signX = 0;
	newY = floor((double)M->pl->y / 32.0) * 32.0 - 1;
	while (newY >= 0)
	{
		newX = pl->x + fabs(pl->y - newY) * tan(ang * PI / 180.0) * signX;
		if (newX < 0 || (int)newX / 32 >= M->map_W[(int)newY / 32] || \
			M->map[(int)newY / 32][(int)newX / 32] == '1')
			break;
		newY -= 32.0;
	}
	M->r_xY = newX;
	M->r_yY = newY;
	return (sqrt(pow(pl->y - newY, 2) + pow(pl->x - newX, 2)));
}

double	find_Y_wall(t_main *M, int cnt, double ang, char flg)
{
	double	newAng;

	newAng = fmod(ang, 90.0);
	if ((ang < 270.0 && ang > 180.0) || ang < 90.0 || ang > 360.0)
		newAng = 90.0 - newAng;
	if (flg)
		M->flg = 'y';
	if (M->pl->rays_ang[cnt] > 180.0 && M->pl->rays_ang[cnt] < 360.0)
		return (cast_up(M, M->pl, cnt, newAng));
	return (cast_down(M, M->pl, cnt, newAng));
}

double	cast_right(t_main *M, t_pl *pl, int cnt, double ang)
{
	int		signY;
	double	newY;
	double	newX;
	char	flg_wall;

	signY = 1;
	flg_wall = 0;
	if (M->pl->rays_ang[cnt] > 270.0)
		signY = -1;
	else if (M->pl->rays_ang[cnt] == 0.0)
		signY = 0;
	newX = floor((double)M->pl->x / 32.0) * 32.0 + 32.0;
	while  (!flg_wall)
	{
		newY = pl->y + fabs(newX - pl->x) * tan(ang * PI / 180.0) * signY;
		if (newY < 0 || newY / 32.0 > M->map_H ||
			newX / 32.0 >= M->map_W[(int)newY / 32] ||
			M->map[(int)newY / 32][(int)newX / 32] == '1')
			flg_wall = 1;
		else
			newX += 32.0;
	}
	M->r_xX = newX;
	M->r_yX = newY;
	return (sqrt(pow(pl->y - newY, 2) + pow(pl->x - newX, 2)));
}

double	cast_left(t_main *M, t_pl *pl, int cnt, double ang)
{
	int		signY;
	double	newY;
	double	newX;

	signY = 1;
	if (M->pl->rays_ang[cnt] > 180.0)
		signY = -1;
	else if (M->pl->rays_ang[cnt] == 180.0)
		signY = 0;
	newX = floor((double)M->pl->x / 32.0) * 32.0 - 1;
	while (newX >= 0)
	{
		newY = pl->y + fabs(newX - pl->x) * tan(ang * PI / 180.0) * signY;
		if ((int)newY / 32 >= M->map_H || newY < 0 ||
			(int)newX / 32 >= M->map_W[(int)newY / 32] ||
			M->map[(int)newY / 32][(int)newX / 32] == '1')
			break;
		newX -= 32.0;
	}
	M->r_xX = newX;
	M->r_yX = newY;
	return (sqrt(pow(pl->y - newY, 2) + pow(pl->x - newX, 2)));
}

double	find_X_wall(t_main *M, int cnt, double ang, char flg)
{
	double	newAng;

	newAng = fmod(ang, 90.0);
	if ((ang < 360.0 && ang > 270.0) || (ang > 90.0 && ang < 180.0))
		newAng = 90.0 - newAng;
	if (flg)
		M->flg = 'x';
	if (M->pl->rays_ang[cnt] < 90.0 || M->pl->rays_ang[cnt] > 270.0)
		return (cast_right(M, M->pl, cnt, newAng));
	return (cast_left(M, M->pl, cnt, newAng));
}