#include "cub.h"

double	cast_horisontal(t_main *m, t_hit *hit, double ang)
{
	int		sign;
	double	new_x;

	sign = 1;
	hit->side = &m->mp->wall_w;
	new_x = (floor(hit->pl_x / 32) + 1) * 32;
	if (ang == 180.0)
	{
		sign = -1;
		hit->side = &m->mp->wall_e;
		new_x = (floor((double)hit->pl_x / 32) * 32) - 0.000001;
	}
	while (new_x >= 0.0 && (int)new_x / 32 < m->map_W[(int)(hit->pl_y / 32)])
	{
		if (get_map_char(m->map, hit->pl_y, new_x) == '1')
			break ;
		new_x += 32.0 * sign;
	}
	hit->flg_wall = 'X';
	return (fabs(new_x - hit->pl_x));
}

double	cast_vertical(t_main *m, t_hit *hit, double ang)
{
	int		sign;
	double	new_y;

	sign = 1;
	hit->side = &m->mp->wall_n;
	new_y = 32.0 * floor(hit->pl_y / 32) + 32;
	if (ang == 270.0)
	{
		sign = -1;
		hit->side = &m->mp->wall_s;
		new_y = 32.0 * floor(hit->pl_y / 32.0) - 0.000001;
	}
	while (new_y >= 0 && (int)new_y / 32 < m->map_H)
	{
		if (get_map_char(m->map, new_y, hit->pl_x) == '1')
			break ;
		new_y += 32.0 * sign;
	}
	hit->flg_wall = 'Y';
	return (fabs(new_y - hit->pl_y));
}