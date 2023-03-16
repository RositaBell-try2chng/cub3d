#include "cub.h"

char	open_walls(t_mlx *mp)
{
	t_img *i;

	i = &mp->wall_w;
	i->img = mlx_xpm_file_to_image(mp->mlx, "texture/wall_W.xpm", &i->w, &i->h);
	i = &mp->wall_e;
	i->img = mlx_xpm_file_to_image(mp->mlx, "texture/wall_E.xpm", &i->w, &i->h);
	i = &mp->wall_n;
	i->img = mlx_xpm_file_to_image(mp->mlx, "texture/wall_N.xpm", &i->w, &i->h);
	i = &mp->wall_s;
	i->img = mlx_xpm_file_to_image(mp->mlx, "texture/wall_S.xpm", &i->w, &i->h);
	if (!mp->wall_w.img || !mp->wall_e.img || \
		!mp->wall_n.img || !mp->wall_s.img)
		return (0);
	mp->wall_w.addr = get_data_img(&mp->wall_w);
	mp->wall_e.addr = get_data_img(&mp->wall_e);
	mp->wall_n.addr = get_data_img(&mp->wall_n);
	mp->wall_s.addr = get_data_img(&mp->wall_s);
	return (1);
}

char    open_rocks(t_mlx *mp)
{
	int     i;
	char    name[] = "rock/rock0.xpm";

	i = -1;
	while (++i < 16)
	{
		if (i < 10)
			name[9] = i + '0';
		else
			name[9] = i - 10 + 'A';
		mp->rock[i].img = mlx_xpm_file_to_image(mp->mlx, name, &mp->rock[i].w, &mp->rock[i].h);
		if (!mp->rock[i].img)
			break;
		mp->rock[i].addr = get_data_img(&mp->rock[i]);
	}
	if (i == 16)
		return (1);
	while (--i >= 0)
		mlx_destroy_image(mp->mlx, mp->rock[i].img);
	mlx_destroy_image(mp->mlx, mp->map.img);
	return (0);
}

void    imgs_init(t_main *m)
{
	m->mp->vis.img = mlx_new_image(m->mp->mlx, 1024, 768);
	if (!m->mp->vis.img)
		init_error_exit(m, 1);
	if (!open_walls(m->mp))
		init_error_exit(m, 2);
	m->mp->map.img = mlx_new_image(m->mp->mlx, M_SIZE, M_SIZE);
	if (!m->mp->map.img)
		init_error_exit(m, 2);
	if (!open_rocks(m->mp))
		init_error_exit(m, 2);
	m->mp->map.addr = get_data_img(&m->mp->map);
	m->mp->vis.addr = get_data_img(&m->mp->vis);
}

static t_pl *save_position(t_main *m, char c, int i, int j)
{
	t_pl *pl = m->pl;
	pl->x = j * 32 + 16;
	pl->y = i * 32 + 16;
	if (c == 'N')
		pl->ang = 270;
	else if (c == 'S')
		pl->ang = 90;
	else if (c == 'W')
		pl->ang = 180;
	else if (c == 'E')
		pl->ang = 0;
	m->map[i][j] = '0';
	return (pl);
}

t_pl    *player_init(t_main *m)
{
	int     i;
	int     j;

	m->pl = malloc(sizeof(t_pl));
	m->pl->flg_trn_l = 0;
	m->pl->flg_trn_r = 0;
	m->pl->flg_move_w = 0;
	m->pl->flg_move_a = 0;
	m->pl->flg_move_s = 0;
	m->pl->flg_move_d = 0;
	i = -1;
	while (m->map[++i])
	{
		j = -1;
		while (m->map[i][++j])
		{
			if (m->map[i][j] != '1' && m->map[i][j] != '0' && \
				m->map[i][j] != ' ')
				return (save_position(m, m->map[i][j], i, j));
		}
	}
	return m->pl;
}