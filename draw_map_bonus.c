/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <rbell@gmail.com>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:46:42 by rbell             #+#    #+#             */
/*   Updated: 2023/03/19 12:46:42 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

void	draw_minimap(t_main *M)
{
	draw_full_back(&M->mp->map, WALL_COLOR);
	draw_no_walls_back(M, M->pl, &M->mp->map);
	draw_player(&M->mp->map);
	draw_direction(&M->mp->map, M->pl, M_HALF - 1);
}
