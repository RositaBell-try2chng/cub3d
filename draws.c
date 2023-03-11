#include "cub.h"

static void	find_start_end(double wall_h, int *st, int *en)
{
	*st = (384 - wall_h / 2);
	*en = (384 + wall_h / 2);
	if (*en > 768)
		(*en) = 768;
}

void	draw_vis(t_main *M, t_hit *hit)
{
	int				y;
	unsigned int	*dst;
	double			wall_h;
	int				wall_start;
	int				wall_end;

	y = 0;
	wall_h = 768.0 * 48 / hit->len;
	find_start_end(wall_h, &wall_start, &wall_end);
	while (y < 768)
	{
		dst = get_pxl_adr(&M->mp->vis, hit->cnt, y);
		if (y >= wall_start && y < wall_end)
			*dst = get_pxl(wall_h, hit, y - wall_start);
		else if (y < 384)
			*dst = UP_COLOR;
		else
			*dst = DOWN_COLOR;
		y++;
	}
}