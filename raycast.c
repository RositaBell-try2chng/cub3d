#include "cub.h"

unsigned int	get_pxl(t_main *M, t_pl *pl, int cnt, int h)
{
	int				x;
	int				y;
	unsigned int	*src;

	if (pl->wall_color[cnt] != WALL_W)
		return (pl->wall_color[cnt]);
	y = h % M->mp->wall_W.h;
	x = cnt % M->mp->wall_W.w;
	src = M->mp->wall_W.addr + y * M->mp->wall_W.line_length + x * (M->mp->wall_W.bits_per_pixel / 8);
	return (*src);
}

void    find_start_end(double wall_size, int *st, int *en)
{
	*st = (384 - ceil(wall_size / 2)) - 1;
	*en = (384 + floor(wall_size / 2));
	if (*st < -1)
		(*st) = -1;
	if (*en > 768)
		(*en) = 768;
}

void    draw_wall(t_main *M, t_pl *pl, int cnt, size_t off_x)
{
	int             wall_start;
	int             wall_end;
	unsigned int    *dst;
	t_img			*vis;

	vis = &M->mp->vis;
	if (pl->rays_len[cnt] <= 0.00001)
	{
		wall_start = -1;
		wall_end = 768;
	}
	else
		find_start_end(768.0 * 8 / pl->rays_len[cnt], &wall_start, &wall_end);
	while (++wall_start < wall_end)
	{
		dst = vis->addr + wall_start * vis->line_length + off_x;
		*dst = get_pxl(M, pl, cnt, wall_start);//pl->wall_color[cnt];
	}
}

void    draw_vis(t_main *M, t_pl *pl, int cnt, size_t off_x)
{
	int             y;
	unsigned int    *dst;
	t_img			*vis;

	vis = &M->mp->vis;
	y = 0;
	while (y < 384)
	{
		dst = vis->addr + (y) * vis->line_length + off_x;
		*dst = UP_COLOR;
		y++;
	}
	while (y < 768)
	{
		dst = vis->addr + (y) * vis->line_length + off_x;
		*dst = DOWN_COLOR;
		y++;
	}
	draw_wall(M, pl, cnt, off_x);
}

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
//	pl->x = 340;
//	pl->y = 54;
//	pl->ang = 278.0;
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
		draw_vis(M, pl, cnt, cnt * (M->mp->vis.bits_per_pixel / 8));
		cnt += 1;
	}
}