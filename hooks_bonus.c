#include "cub.h"

int	ft_red_cross(t_main *m)
{
	int	i;

	i = 0;
	printf("x = %lf, y = %lf, ang = %lf\n", m->pl->x, m->pl->y, m->pl->ang);
	free(m->pl);
	while (m->map && m->map[i])
		free(m->map[i++]);
	mlx_destroy_image(m->mp->mlx, m->mp->vis.img);
	mlx_destroy_image(m->mp->mlx, m->mp->map.img);
	mlx_destroy_image(m->mp->mlx, m->mp->wall_w.img);
	mlx_destroy_image(m->mp->mlx, m->mp->wall_e.img);
	mlx_destroy_image(m->mp->mlx, m->mp->wall_n.img);
	mlx_destroy_image(m->mp->mlx, m->mp->wall_s.img);
	mlx_destroy_window(m->mp->mlx, m->mp->win);
	free(m->mp);
	free(m->map);
	exit(0);
}

int	ft_press(int key, t_main *m)
{
	if (key == ESC)
		ft_red_cross(m);
	else if (key == W)
		m->pl->flg_move_w = 1;
	else if (key == A)
		m->pl->flg_move_a = -1;
	else if (key == S)
		m->pl->flg_move_s = -1;
	else if (key == D)
		m->pl->flg_move_d = 1;
	else if (key == RIGHT_ARROW)
		m->pl->flg_trn_r = 1;
	else if (key == LEFT_ARROW)
		m->pl->flg_trn_l = 1;
	else
		printf("unknown key = %d\n", key);
	return (0);
}

int	ft_release(int key, t_main *m)
{
	if (key == W)
		m->pl->flg_move_w = 0;
	else if (key == A)
		m->pl->flg_move_a = 0;
	else if (key == S)
		m->pl->flg_move_s = 0;
	else if (key == D)
		m->pl->flg_move_d = 0;
	else if (key == RIGHT_ARROW)
		m->pl->flg_trn_r = 0;
	else if (key == LEFT_ARROW)
		m->pl->flg_trn_l = 0;
	return (0);
}