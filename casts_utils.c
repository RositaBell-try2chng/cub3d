/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <rbell@gmail.com>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:46:42 by rbell             #+#    #+#             */
/*   Updated: 2023/03/19 12:46:42 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

char	check_correct(t_main *m, double x, double y, char *flg)
{
	if ((int)y < 0 || (int)y / 32 >= m->map_h || \
		(int)x < 0 || (int)x / 32 >= m->map_w[(int)y / 32])
	{
		*flg = 0;
		return (0);
	}
	return (1);
}

char	check_wall(t_main *m, double x, double y)
{
	if (get_map_char(m->map, y, x) == '1')
		return (1);
	return (0);
}
