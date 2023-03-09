#include "cub.h"

double	set_hit_value(double res, double ang)
{
	double	hit;

	hit = res * sin(ang * PI / 180.0);
	hit -= floor(hit);
	return (hit);
}

static unsigned int	*take_src(t_main *M, int cnt, double wall_h, int h)
{
	unsigned int	*res;
	int				col;
	int				row;
	t_img			*img;

	img = &M->mp->wall_W;
	row = h / ceil(wall_h / 64);
	col = (int)(M->pl->hit_value[cnt] * 64);
	res = img->addr + row * img->line_length + col * (img->bits_per_pixel / 8);
	//printf("row = %d, col = %d\n", row, col);
	return (res);
}

unsigned int	get_pxl(t_main *M, double wall_h, int cnt, int h)
{
	unsigned int	*src;

	if (M->pl->wall_color[cnt] == WALL_W)
		src = take_src(M, cnt, wall_h, h);
	else
		return (M->pl->wall_color[cnt]);
	return (*src);
}

unsigned int	*get_dst(t_img *img, int x, int y)
{
	return (img->addr + y * img->line_length + x * (img->bits_per_pixel / 8));
}