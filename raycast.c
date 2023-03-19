/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <rbell@gmail.com>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:46:42 by rbell             #+#    #+#             */
/*   Updated: 2023/03/19 12:46:42 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

double	math_need_len(double real, double ang)
{
	return (real * sin((90.0 - ang) * PI / 180));
}

double	math_ray_len(t_main *m, t_hit *hit, double ang)
{
	if (fmod(ang, 90.0) == 0.0)
	{
		if (ang == 90.0 || ang == 270.0)
			return (cast_vertical(m, hit, ang));
		return (cast_horisontal(m, hit, ang));
	}
	if ((ang > 0.0 && ang < 90.0) || ang > 360.0)
		return (cast_right_down(m, hit));
	else if (ang > 90.0 && ang < 180.0)
		return (cast_left_down(m, hit));
	else if (ang > 180.0 && ang < 270.0)
		return (cast_left_up(m, hit));
	return (cast_right_up(m, hit));
}

static void	prepare_hit(t_main *m, t_hit *hit)
{
	hit->ang = (m->pl->ang + ((double)hit->cnt * 50.0 / 1024.0) - 25.0);
	if (hit->ang >= 360.0)
		hit->ang -= 360.0;
	else if (hit->ang < 0.0)
		hit->ang += 360.0;
	hit->len = 0.0;
	hit->x_y = m->pl->y;
	hit->y_x = m->pl->x;
	hit->pl_ang = m->pl->ang;
	hit->flg_wall = 0;
	hit->side = &m->mp->wall_w;
	hit->pl_x = m->pl->x;
	hit->pl_y = m->pl->y;
}

void	cast_rays(t_main *m, t_pl *pl)
{
	t_hit	hit;

	hit.cnt = 0;
	while (hit.cnt < 1024)
	{
		prepare_hit(m, &hit);
		hit.len = math_ray_len(m, &hit, hit.ang);
		hit.len *= sin((90 - fabs(pl->ang - hit.ang)) * PI / 180);
		draw_vis(m, &hit);
		hit.cnt += 1;
	}
}
