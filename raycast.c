#include "cub.h"

void    find_start_end(double wall_size, int *st, int *en)
{
	/*if (wall_size < 1)
	{
		(*st) = 0;
		(*en) = 0;
		return;
	}*/
	*st = (384 - (int)wall_size / 2);
	*en = (384 + (int)wall_size / 2);
	if (*st < -1)
		(*st) = -1;
	if (*en > 768)
		(*en) = 768;
}

void    draw_wall(t_img *vis, t_pl *pl, int cnt, size_t off_x)
{
	int             wall_start;
	int             wall_end;
	unsigned int    *dst;

	if (pl->rays_len[cnt] == 0.0)
	{
		wall_start = -1;
		wall_end = 768;
	}
	else
		find_start_end(768.0 * 4 / pl->rays_len[cnt], &wall_start, &wall_end);
	while (++wall_start < wall_end)
	{
		dst = vis->addr + wall_start * vis->line_length + off_x;
		*dst = pl->wall_color[cnt];
	}
}

void    draw_vis(t_img *vis, t_pl *pl, int cnt, size_t off_x)
{
	int             y;
	unsigned int    *dst;

	y = 0;
	while (y < 384)
	{
		dst = vis->addr + (y) * vis->line_length + off_x;
		*dst = UP_COLOR;
		y++;
	}
	while (y < 768)
	{
		dst = vis->addr + (y) * vis->line_length + off_x;
		*dst = DOWN_COLOR;
		y++;
	}
	draw_wall(vis, pl, cnt, off_x);
}

unsigned int set_wall_color(t_main *M, t_pl *pl, size_t y, size_t x)
{
	char flg_x = 0; //0 - norm, -1 - no left_check, 1 - no right_check
	char flg_y = 0; //0 - norm, -1 - no up_check, 1 - no down_check

	if ((int)y / 32 - 1 < 0 || (int)x / 32 >= M->map_W[y / 32 - 1])
		flg_y = -1;
	if ((int)x / 32 - 1 < 0)
		flg_x = -1;
	if ((int)y / 32 + 1 >= M->map_H || (int)x / 32 >= M->map_W[y / 32 + 1])
		flg_y = 1;
	if ((int)x / 32 + 1 >= M->map_W[y / 32])
		flg_x = 1;
	if (x % 32 == 0 && y % 32 == 0)
	{
		if ((flg_x >= 0) && (M->map[y / 32][x / 32 - 1] == '1'))
			return (WALL_N);
		if ((flg_y >= 0) && (M->map[y / 32 - 1][x / 32] == '1'))
			return (WALL_W);
		if (pl->x >= x || (pl->x <= x && pl->y <= y && pl->ang > 45))
			return (WALL_N);
		if (pl->y >= y || (pl->x <= x && pl->y < y && pl->ang <= 45))
			return (WALL_W);
	}
	else if (x % 32 == 0 && (y + 1) % 32 == 0)
	{
		if ((flg_x >= 0) && (M->map[y / 32][x / 32 - 1] == '1'))
			return (WALL_S);
		if ((flg_y <= 0) && (M->map[y / 32 + 1][x / 32] == '1'))
			return (WALL_W);
		if (pl->x >= x || (pl->x < x && pl->y > y && pl->ang < 315))
			return (WALL_S);
		if (pl->y <= y || (pl->x < x && pl->y > y && pl->ang >= 315)) {
			return (WALL_W);
		}
	}
	else if (y % 32 == 0 && (x + 1) % 32 == 0)
	{
		if ((flg_x <= 0) && (M->map[y / 32][x / 32 + 1] == '1'))
			return (WALL_N);
		if ((flg_y >= 0) && (M->map[y / 32 - 1][x / 32] == '1'))
			return (WALL_E);
		if (pl->x <= x || (pl->x > x && pl->y < y && pl->ang < 135))
			return (WALL_N);
		if (pl->y >= y || (pl->x > x && pl->y < y && pl->ang >= 135))
			return (WALL_E);
	}
	else if ((x + 1) % 32 == 0 && (y + 1) % 32 == 0)
	{
		if ((flg_x <= 0) && (M->map[y / 32][x / 32 + 1] == '1'))
			return (WALL_S);
		if ((flg_y <= 0) && (M->map[y / 32 + 1][x / 32] == '1'))
			return (WALL_E);
		if (pl->x <= x || (pl->x > x && pl->y < y && pl->ang > 225))
			return (WALL_S);
		if (pl->y <= y || (pl->x > x && pl->y > y && pl->ang <= 225))
			return (WALL_E);
	}
	return (BLACK_COLOR);
}

unsigned int    math_wall_color(t_main *M, int r_x, int r_y, t_pl *pl)
{
	if ((r_x - 0) % 32 == 0 && r_y % 32 != 0 && (r_y - 1) % 32 != 0)
		return (WALL_W);
	if ((r_x - 1) % 32 == 0 && r_y % 32 != 0 && (r_y - 1) % 32 != 0)
		return (WALL_E);
	if ((r_y - 0) % 32 == 0 && r_x % 32 != 0 && (r_x - 1) % 32 != 0)
		return (WALL_N);
	if ((r_y - 1) % 32 == 0 && r_x % 32 != 0 && (r_x - 1) % 32 != 0)
		return (WALL_S);
	return (set_wall_color(M, pl, r_y, r_x));
}

double  math_need_len(double real, double ang)
{
	return (real * sin((90.0 - ang) * PI / 180));
}

/*void  math_ray_len1(t_main *M, t_pl *pl, int cnt)
{
	double	r_x;
	double	r_y;
	int 	flg_wall;

	flg_wall = 0;
	while (!flg_wall)
	{
		r_x = (double)pl->x + pl->rays_len[cnt] * cos(pl->rays_ang[cnt] * PI / 180.0);
		r_y = (double)pl->y + pl->rays_len[cnt] * sin(pl->rays_ang[cnt] * PI / 180.0);
		if (M->map[(int)r_y / 32][(int)r_x / 32] == '1')
			flg_wall = 1;
		else
			pl->rays_len[cnt] += 0.05;
	}
	pl->rays_len[cnt] = math_need_len(pl->rays_len[cnt], pl->ang - pl->rays_ang[cnt]);
	pl->wall_color[cnt] = math_wall_color(M, r_x, r_y, pl);
}
*/

double  math_ray_len(t_main *M, int cnt, double ang)
{
	if (fmod(ang, 90.0) == 0.0)
	{
		if (ang == 90.0 || ang == 270.0)
			return (cast_vertical(M, pl, cnt, ang));
		return (cast_horisontal(M, pl, cnt, ang));
	}
	if ((ang > 0.0 && ang < 90.0) || ang > 360.0)
		return (cast_right_down(M, pl, cnt));
	else if (ang > 90.0 && ang < 180.0)
		return (cast_left_down(M, pl, cnt));
	else if (ang > 180.0 && ang < 270.0)
		return (cast_left_up(M, pl, cnt));
	return (cast_right_up(M, pl, cnt));
}

void    cast_rays(t_main *M, t_pl *pl)
{
	int     cnt;


	cnt = 0;
//	pl->x = 992;
//	pl->y = 35;
//	pl->ang = 78.0;
	while (cnt < 1024)
	{
		pl->rays_ang[cnt] = (pl->ang + ((double)cnt * 90.0 / 1024.0) - 45);
		if (pl->rays_ang[cnt] >= 360.0)
			pl->rays_ang[cnt] -= 360.0;
		else if (pl->rays_ang[cnt] < 0.0)
			pl->rays_ang[cnt] += 360.0;
		pl->rays_len[cnt] = 0;
		pl->rays_len[cnt] = math_ray_len(M, cnt, pl->rays_ang[cnt]);
		pl->rays_len[cnt] = math_need_len(pl->rays_len[cnt], fabs(pl->ang - pl->rays_ang[cnt]));
		if (M->flg == 'x')
			pl->wall_color[cnt] = math_wall_color(M, M->r_xX, M->r_yX, pl);
		else
			pl->wall_color[cnt] = math_wall_color(M, M->r_xY, M->r_yY, pl);
		draw_vis(&M->mp->vis, pl, cnt, cnt * (M->mp->vis.bits_per_pixel / 8));
		cnt += 1;
	}
}