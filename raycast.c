#include "cub.h"

double  math_need_len(double real, double ang)
{
	return (real * sin((90.0 - ang) * PI / 180));
}

double  math_ray_len(t_main *M, t_pl *pl, int cnt, double ang)
{
	if (fmod(ang, 90.0) == 0.0)
	{
		if (ang == 90.0 || ang == 270.0)
			return (cast_vertical(M, pl, cnt, ang));
		return (cast_horisontal(M, pl, cnt, ang));
	}
	if ((ang > 0.0 && ang < 90.0) || ang > 360.0)
		return (cast_right_down(M, pl, cnt));
	else if (ang > 90.0 && ang < 180.0)
		return (cast_left_down(M, pl, cnt));
	else if (ang > 180.0 && ang < 270.0)
		return (cast_left_up(M, pl, cnt));
	return (cast_right_up(M, pl, cnt));
}

void    cast_rays(t_main *M, t_pl *pl)
{
	int     cnt;


	cnt = 0;
//	pl->x = 769;
//	pl->y = 105;
//	pl->ang = 6.0;
	while (cnt < 1024)
	{
		pl->rays_ang[cnt] = (pl->ang + ((double)cnt * 30.0 / 1024.0) - 15.0);
		if (pl->rays_ang[cnt] >= 360.0)
			pl->rays_ang[cnt] -= 360.0;
		else if (pl->rays_ang[cnt] < 0.0)
			pl->rays_ang[cnt] += 360.0;
		pl->rays_len[cnt] = 0;
		pl->rays_len[cnt] = math_ray_len(M, pl, cnt, pl->rays_ang[cnt]);
		pl->rays_len[cnt] *= sin((90 - fabs(pl->ang - pl->rays_ang[cnt])) * PI / 180);
		draw_vis(M, pl, cnt);
		cnt += 1;
	}
}