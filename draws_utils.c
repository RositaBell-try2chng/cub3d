/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draws_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <rbell@gmail.com>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:46:42 by rbell             #+#    #+#             */
/*   Updated: 2023/03/19 12:46:42 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

static double	get_diff_border(double k)
{
	return (k - floor(k / SCALE) * SCALE);
}

unsigned int	get_pxl(double wall_h, t_hit *hit, int h)
{
	double			k;
	int				x;
	int				y;

	if (hit->flg_wall == 'Y')
	{
		x = (int)(get_diff_border(hit->y_x) / SCALE * hit->side->w);
		if (hit->pl_ang > 0.0 && hit->pl_ang < 180.0)
			x = hit->side->w - x - 1;
	}
	else
	{
		x = (int)(get_diff_border(hit->x_y) / SCALE * hit->side->w);
		if (hit->pl_ang < 270.0 && hit->pl_ang > 90.0)
			x = hit->side->w - x - 1;
	}
	k = wall_h / hit->side->h;
	y = (int)((double)h / k);
	return (*get_pxl_adr(hit->side, x, y));
}

unsigned int	*get_pxl_adr(t_img *img, int x, int y)
{
	return (img->addr + y * img->line_length + x * (img->bits_per_pixel / 8));
}
