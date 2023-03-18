#include "cub.h"

char	check_walls(char **map, double x, double y)
{
	if (get_map_char(map, y - 2, x - 2) == '1' || \
		get_map_char(map, y - 2, x + 2) == '1' || \
		get_map_char(map, y + 2, x + 2) == '1' || \
		get_map_char(map, y + 2, x - 2) == '1')
		return (1);
	return (0);
}

void	move_cnt_recursive(t_move *mv, char flg, char step)
{
	double	k;

	if (step == 8)
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

void	move_cnt(t_main *m, t_pl *pl, double ang, int speed)
{
	t_move	mv;

	mv.pl = pl;
	mv.map = m->map;
	mv.ang = ang;
	mv.speed = speed;
	if (ang > 315.0 || ang <= 45 || (ang >= 135.0 && ang < 225.0))
		move_cnt_recursive(&mv, 'y', 0);
	else
		move_cnt_recursive(&mv, 'x', 0);
}

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