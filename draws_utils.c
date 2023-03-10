#include "cub.h"

double	set_hit_value(double res, double ang)
{
	double	hit;

	hit = res * sin(ang * PI / 180.0);
	hit /= SCALE;
	hit -= floor(hit);
	return (hit);
}

/*static unsigned int	*take_src(t_img *img, int x, int y)
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
}*/

unsigned int	get_pxl(double wall_h, t_hit *hit, int h)
{
	double			k;
	int				x;
	int				y;

	if (hit->flg_wall == 'Y')
	{
		x = (int)((hit->Y_x - floor(hit->Y_x / SCALE) * SCALE) / SCALE * hit->side->w);
		k = wall_h / hit->side->h;
		y = (int)floor((double)h / k);
	}
	else
	{
		y = (int)((hit->X_y - floor(hit->X_y / SCALE) * SCALE) / SCALE * hit->side->h);
		k = wall_h / hit->side->w;
		x = (int)floor((double)h / k);
	}
	return (*get_pxl_adr(hit->side, x, y));
}

unsigned int	*get_pxl_adr(t_img *img, int x, int y)
{
	return (img->addr + y * img->line_length + x * (img->bits_per_pixel / 8));
}