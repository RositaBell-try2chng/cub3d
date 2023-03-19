/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <rbell@gmail.com>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:46:42 by rbell             #+#    #+#             */
/*   Updated: 2023/03/19 12:46:42 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

static void	move(t_main *m, t_pl *pl)
{
	int		speed;
	double	ang;

	ang = pl->ang;
	speed = define_speed_ang(pl, &ang);
	move_cnt(m, pl, ang, speed);
}

static void	turn(t_pl *pl)
{
	if (pl->flg_trn_r == 1 && pl->flg_trn_l == 0)
		pl->ang += 3;
	else if (pl->flg_trn_r == 0 && pl->flg_trn_l == 1)
		pl->ang -= 3;
	if (pl->ang > 360)
		pl->ang -= 360;
	if (pl->ang < 0)
		pl->ang += 360;
}

void	moves(t_main *m, t_pl *pl)
{
	turn(pl);
	move(m, pl);
}
