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
	newY = 32.0 * floor((double)pl->y / 32.0) + 32.0;
	if (ang == 270.0)
	{
		sign = -1;
		pl->wall_color[cnt] = WALL_S;
		newY = 32.0 * floor((double)pl->y / 32.0) - 0.000001;
	}
	while (newY >= 0 && (int)newY / 32 < M->map_H)
	{
		if (M->map[(int)newY / 32][pl->x / 32] == '1')
			break;
		newY += 32.0 * sign;
	}
	return (fabs(newY - pl->y));
}