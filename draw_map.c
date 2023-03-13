#include "cub.h"

// Minimap
static void	draw_player(t_img *map)
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
static void	draw_no_walls_back(t_main *M, t_pl *pl, t_img *map)
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
static void	draw_direction(t_img *map, t_pl *pl, int k)
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
static void	draw_full_back(t_img *map, int color)
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

void	draw_minimap(t_main *M)
{
	draw_full_back(&M->mp->map, WALL_COLOR);
	draw_no_walls_back(M, M->pl, &M->mp->map);
	draw_player(&M->mp->map);
	draw_direction(&M->mp->map, M->pl, M_HALF - 1);
}