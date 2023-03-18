#include "cub.h"

int draw_frame(t_main *m)
{
	moves(m, m->pl);
	drawers(m, m->pl);
	puts_img(m->mp->mlx, m->mp->win, m->mp);
    return (0);
}

static void    draw_full_vis(t_img *vis)
{
	size_t          i;
	size_t          j;
	unsigned int    *dst;

	i = -1;
	while (++i < 768)
	{
		j = -1;
		while (++j < 1024)
		{
			dst = get_pxl_adr(vis, j, i);
			*dst = GREY_COLOR;
		}
	}
}

void game_play(t_main *m)
{
	m->pl = player_init(m);
	m->mp->mlx = mlx_init();
	m->mp->win = mlx_new_window(m->mp->mlx, 1024, 768, "cub3d");
	if (!m->mp->win)
		init_error_exit(m, 0);
	imgs_init(m);
	draw_full_vis(&m->mp->vis);
	mlx_hook(m->mp->win, 2, 1L << 0, ft_press, m);
	mlx_hook(m->mp->win, 3, 1L << 1, ft_release, m);
	mlx_hook(m->mp->win, 17, 1L << 17, ft_red_cross, m);
	mlx_loop_hook(m->mp->mlx, draw_frame, m);
	mlx_loop(m->mp->mlx);
}