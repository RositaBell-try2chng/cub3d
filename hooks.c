/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <rbell@gmail.com>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:46:42 by rbell             #+#    #+#             */
/*   Updated: 2023/03/19 12:46:42 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

static void	free_walls(t_main *m)
{
	free(m->path_east);
	free(m->path_west);
	free(m->path_north);
	free(m->path_south);
}

int	ft_red_cross(t_main *m)
{
	int	i;

	i = 0;
	free(m->pl);
	while (m->map && m->map[i])
		free(m->map[i++]);
	free(m->map_w);
	free_walls(m);
	mlx_destroy_image(m->mp->mlx, m->mp->vis.img);
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
