#include "cub.h"

double	cast_horisontal(t_main *M, t_hit *hit, double ang)
{
	int		sign;
	double	newX;

	sign = 1;
	hit->side = &M->mp->wall_W;
	newX = (floor(hit->pl_x / 32) + 1) * 32;
	if (ang == 180.0)
	{
		sign = -1;
		hit->side = &M->mp->wall_E;
		newX = (floor((double)hit->pl_x / 32) * 32) - 0.000001;
	}
	while (newX >= 0.0 && (int)newX / 32 < M->map_W[(int)(hit->pl_y / 32)])
	{
		if (M->map[(int)(hit->pl_y / 32)][(int)(newX / 32)] == '1')
			break;
		newX += 32.0 * sign;
	}
	hit->flg_wall = 'X';
	return (fabs(newX - hit->pl_x));
}

double	cast_vertical(t_main *M, t_hit *hit, double ang)
{
	int		sign;
	double	newY;

	sign = 1;
	hit->side = &M->mp->wall_N;
	newY = 32.0 * floor(hit->pl_y / 32) + 32;
	if (ang == 270.0)
	{
		sign = -1;
		hit->side = &M->mp->wall_S;
		newY = 32.0 * floor(hit->pl_y / 32.0) - 0.000001;
	}
	while (newY >= 0 && (int)newY / 32 < M->map_H)
	{
		if (M->map[(int)(newY / 32)][(int)(hit->pl_x / 32)] == '1')
			break;
		newY += 32.0 * sign;
	}
	hit->flg_wall = 'Y';
	return (fabs(newY - hit->pl_y));
}