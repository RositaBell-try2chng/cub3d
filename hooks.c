#include "cub.h"

int	ft_red_cross(t_main *Main)
{
	int	i;

	i = 0;
	printf("x = %lf, y = %lf, ang = %lf\n", Main->pl->x, Main->pl->y, Main->pl->ang);
	free(Main->pl);
	while (Main->map && Main->map[i])
		free(Main->map[i++]);
	mlx_destroy_image(Main->mp->mlx, Main->mp->vis.img);
	mlx_destroy_image(Main->mp->mlx, Main->mp->map.img);
	mlx_destroy_image(Main->mp->mlx, Main->mp->wall_W.img);
	mlx_destroy_image(Main->mp->mlx, Main->mp->wall_E.img);
	mlx_destroy_image(Main->mp->mlx, Main->mp->wall_N.img);
	mlx_destroy_image(Main->mp->mlx, Main->mp->wall_S.img);
	mlx_destroy_window(Main->mp->mlx, Main->mp->win);
	free(Main->mp);
	free(Main->map);
	exit(0);
}

int	ft_press(int key, t_main *Main)
{
	if (key == ESC)
		ft_red_cross(Main);
	else if (key == W)
		Main->pl->flg_move_w = 1;
	else if (key == A)
		Main->pl->flg_move_a = 1;
	else if (key == S)
		Main->pl->flg_move_s = 1;
	else if (key == D)
		Main->pl->flg_move_d = 1;
	else if (key == RIGHT_ARROW)
		Main->pl->flg_trn_r = 1;
	else if (key == LEFT_ARROW)
		Main->pl->flg_trn_l = 1;
	else
		printf("unknown key = %d\n", key);
	return (0);
}

int	ft_release(int key, t_main *Main)
{
	if (key == W)
		Main->pl->flg_move_w = 0;
	else if (key == A)
		Main->pl->flg_move_a = 0;
	else if (key == S)
		Main->pl->flg_move_s = 0;
	else if (key == D)
		Main->pl->flg_move_d = 0;
	else if (key == RIGHT_ARROW)
		Main->pl->flg_trn_r = 0;
	else if (key == LEFT_ARROW)
		Main->pl->flg_trn_l = 0;
	return (0);
}