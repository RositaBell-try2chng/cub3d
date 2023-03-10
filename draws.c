#include "cub.h"

static void    find_start_end(double wall_h, int *st, int *en)
{
	*st = (384 - ceil(wall_h / 2));
	*en = (384 + floor(wall_h / 2));
	if (*st < 0)
		(*st) = 0;
	if (*en > 768)
		(*en) = 768;
}

static void    draw_wall(t_main *M, t_hit *hit)
{
	int             wall_start;
	int             wall_end;
	unsigned int    *dst;
	double			wall_h;
	int				i;

	wall_h = 768.0 * 4 / hit->len;
	if (hit->len <= 0.00001)
	{
		wall_start = 0;
		wall_end = 768;
	}
	else
		find_start_end(wall_h, &wall_start, &wall_end);
	i = -1;
	while (++i + wall_start < wall_end)
	{
		dst = get_pxl_adr(&M->mp->vis, hit->cnt, wall_start + i);
		*dst = get_pxl(wall_h, hit, i);
	}
}

void    draw_vis(t_main *M, t_hit *hit)
{
	int             y;
	unsigned int    *dst;
	t_img			*vis;

	vis = &M->mp->vis;
	y = 0;
	while (y < 384)
	{
		dst = get_pxl_adr(vis, hit->cnt, y);
		*dst = UP_COLOR;
		y++;
	}
	while (y < 768)
	{
		dst = get_pxl_adr(vis, hit->cnt, y);
		*dst = DOWN_COLOR;
		y++;
	}
	draw_wall(M, hit);
}