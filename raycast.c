#include "cub.h"

double	math_need_len(double real, double ang)
{
	return (real * sin((90.0 - ang) * PI / 180));
}

double	math_ray_len(t_main *M, t_hit *hit, double ang)
{
	if (fmod(ang, 90.0) == 0.0)
	{
		if (ang == 90.0 || ang == 270.0)
			return (cast_vertical(M, hit, ang));
		return (cast_horisontal(M, hit, ang));
	}
	if ((ang > 0.0 && ang < 90.0) || ang > 360.0)
		return (cast_right_down(M, hit));
	else if (ang > 90.0 && ang < 180.0)
		return (cast_left_down(M, hit));
	else if (ang > 180.0 && ang < 270.0)
		return (cast_left_up(M, hit));
	return (cast_right_up(M, hit));
}

static void	prepare_hit(t_main *M, t_hit *hit)
{
	hit->ang = (M->pl->ang + ((double)hit->cnt * 50.0 / 1024.0) - 25.0);
	if (hit->ang >= 360.0)
		hit->ang -= 360.0;
	else if (hit->ang < 0.0)
		hit->ang += 360.0;
	hit->len = 0.0;
	hit->x_y = M->pl->y;
	hit->y_x = M->pl->x;
	hit->flg_wall = 0;
	hit->side = &M->mp->wall_W;
	hit->pl_x = M->pl->x;
	hit->pl_y = M->pl->y;
}

void	cast_rays(t_main *M, t_pl *pl)
{
	t_hit	hit;

	hit.cnt = 0;
	while (hit.cnt < 1024)
	{
		prepare_hit(M, &hit);
		hit.len = math_ray_len(M, &hit, hit.ang);
		hit.len *= sin((90 - fabs(pl->ang - hit.ang)) * PI / 180);
		draw_vis(M, &hit);
		hit.cnt += 1;
	}
}