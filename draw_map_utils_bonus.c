#include "cub.h"

char	check_border_minimap(t_main *M, int p, int c, int flg)
{
	int	res;
	int	dop;

	res = p - M_HALF + c;
	if (flg == -1)
	{
		if (res < 0 || res / 32 >= M->map_H)
			return (1);
		return (0);
	}
	dop = M->pl->y - M_HALF + flg;
	if (res < 0 || (res) / 32 >= M->map_W[dop / 32])
		return (1);
	return (0);
}

// Minimap
void	draw_player(t_img *map)
{
	int				i;
	int				j;
	unsigned int	*dst;

	i = -1;
	while (++i < 6)
	{
		j = -1;
		while (++j < 6)
		{
			dst = get_pxl_adr(map, j + M_HALF - 3, i + M_HALF - 3);
			*dst = PL_COLOR;
		}
	}
}

// Minimap
void	draw_no_walls_back(t_main *M, t_pl *pl, t_img *map)
{
	int				y;
	int				x;
	char			c;
	unsigned int	*dst;

	y = -1;
	while (++y < M_SIZE)
	{
		if (check_border_minimap(M, pl->y, y, -1))
			continue ;
		x = -1;
		while (++x < M_SIZE)
		{
			if (check_border_minimap(M, pl->x, x, y))
				continue ;
			c = get_map_char(M->map, pl->y - M_HALF + y, pl->x - M_HALF + x);
			dst = get_pxl_adr(map, x, y);
			if (c == '0')
				*dst = FLOOR_COLOR;
		}
	}
}

// Minimap
void	draw_direction(t_img *map, t_pl *pl, int k)
{
	unsigned int	*ray;
	double			k_x;
	double			k_y;
	double			ray_len;

	ray_len = 0.0;
	while (ray_len < 25.0)
	{
		k_x = ray_len * cos(pl->ang * PI / 180);
		k_y = ray_len * sin(pl->ang * PI / 180);
		ray = get_pxl_adr(map, ((int) k_x + k), ((int) k_y + k));
		if (*ray == WALL_COLOR)
			break ;
		else
			*ray = RAY_COLOR;
		ray_len += 0.5;
	}
}

//minimap
void	draw_full_back(t_img *map, int color)
{
	int				i;
	int				j;
	unsigned int	*dst;

	i = -1;
	while (++i < M_SIZE)
	{
		j = -1;
		while (++j < M_SIZE)
		{
			dst = get_pxl_adr(map, j, i);
			*dst = color;
		}
	}
}