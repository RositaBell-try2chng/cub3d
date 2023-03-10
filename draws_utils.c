#include "cub.h"

unsigned int	get_pxl(double wall_h, t_hit *hit, int h)
{
	double			k;
	int				x;
	int				y;

	if (hit->flg_wall == 'Y')
	{
		x = (int)((hit->Y_x - floor(hit->Y_x / SCALE) * SCALE) / SCALE * hit->side->w);
		k = wall_h / hit->side->h;
		y = (int)((double)h / k);
	}
	else
	{
		y = (int)((hit->X_y - floor(hit->X_y / SCALE) * SCALE) / SCALE * hit->side->h);
		k = wall_h / hit->side->w;
		x = (int)((double)h / k);
	}
	return (*get_pxl_adr(hit->side, x, y));
}

unsigned int	*get_pxl_adr(t_img *img, int x, int y)
{
	return (img->addr + y * img->line_length + x * (img->bits_per_pixel / 8));
}