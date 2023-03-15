#include "cub.h"

static double	find_x_wall(t_main *m, t_hit *hit, char *flg)
{
	double	new_x;
	double	new_y;
	char	flg_wall;
	double	ang;

	flg_wall = 0;
	ang = 90.0 - fmod(hit->ang, 90.0);
	new_x = (floor(hit->pl_x / 32) + 1) * 32.0;
	while (!flg_wall)
	{
		new_y = hit->pl_y - (new_x - hit->pl_x) * tan(ang * PI / 180.0);
		if (!check_correct(m, new_x, new_y, flg))
			return (-1);
		else if (check_wall(m, new_x, new_y))
			flg_wall = 1;
		else
			new_x += 32.0;
	}
	hit->x_y = new_y;
	return (sqrt(pow(new_y - hit->pl_y, 2) + pow(new_x - hit->pl_x, 2)));
}

static double	find_y_wall(t_main *m, t_hit *hit, char *flg)
{
	double	new_x;
	double	new_y;
	char	flg_wall;
	double	ang;

	flg_wall = 0;
	ang = fmod(hit->ang, 90.0);
	new_y = (floor(hit->pl_y / 32) * 32.0) - 0.000001;
	while (!flg_wall)
	{
		new_x = hit->pl_x + (hit->pl_y - new_y) * tan(ang * PI / 180.0);
		if (!check_correct(m, new_x, new_y, flg))
			return (-1);
		else if (check_wall(m, new_x, new_y))
			flg_wall = 1;
		else
			new_y -= 32.0;
	}
	hit->y_x = new_x;
	return (sqrt(pow(new_y - hit->pl_y, 2) + pow(new_x - hit->pl_x, 2)));
}

double	cast_right_up(t_main *m, t_hit *hit)
{
	double	res_x;
	double	res_y;
	char	flg_correct_x;
	char	flg_correct_y;

	flg_correct_x = 1;
	flg_correct_y = 1;
	res_x = find_x_wall(m, hit, &flg_correct_x);
	res_y = find_y_wall(m, hit, &flg_correct_y);
	if (!flg_correct_x && !flg_correct_y)
		exit(printf("incorrect flags\n"));
	if ((res_x <= res_y && flg_correct_x) || !flg_correct_y)
	{
		hit->flg_wall = 'X';
		hit->side = &m->mp->wall_w;
		return (res_x);
	}
	hit->flg_wall = 'Y';
	hit->side = &m->mp->wall_s;
	return (res_y);
}