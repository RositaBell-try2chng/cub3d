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

void	drawers(t_main *m, t_pl *pl)
{
	cast_rays(m, pl);
	draw_minimap(m);
}

void	puts_img(void *mlx, void *win, t_mlx *mp)
{
	static int	cnt;

	mlx_put_image_to_window(mlx, win, mp->vis.img, 0, 0);
	mlx_put_image_to_window(mlx, win, mp->map.img, 0, 0);
	mlx_put_image_to_window(mlx, win, mp->rock[cnt / 8].img, 450, 10);
	cnt++;
	if (cnt == 15 * 8)
		cnt = 0;
}