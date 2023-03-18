#include "cub.h"

char	open_walls(t_mlx *mp)
{
	t_img *i;

	i = &mp->wall_w;
	i->img = mlx_xpm_file_to_image(mp->mlx, "texture/WALL_W.xpm", &i->w, &i->h);
	i = &mp->wall_e;
	i->img = mlx_xpm_file_to_image(mp->mlx, "texture/WALL_E.xpm", &i->w, &i->h);
	i = &mp->wall_n;
	i->img = mlx_xpm_file_to_image(mp->mlx, "texture/WALL_N.xpm", &i->w, &i->h);
	i = &mp->wall_s;
	i->img = mlx_xpm_file_to_image(mp->mlx, "texture/WALL_S.xpm", &i->w, &i->h);

	if (!mp->wall_w.img || !mp->wall_e.img || \
		!mp->wall_n.img || !mp->wall_s.img)
		return (0);
	mp->wall_w.addr = get_data_img(&mp->wall_w);
	mp->wall_e.addr = get_data_img(&mp->wall_e);
	mp->wall_n.addr = get_data_img(&mp->wall_n);
	mp->wall_s.addr = get_data_img(&mp->wall_s);
	return (1);
}

void    imgs_init(t_main *m)
{
	m->mp->vis.img = mlx_new_image(m->mp->mlx, 1024, 768);
	if (!m->mp->vis.img)
		init_error_exit(m, 1);
	if (!open_walls(m->mp))
		init_error_exit(m, 2);
	m->mp->vis.addr = get_data_img(&m->mp->vis);
}

static t_pl *save_position(t_main *main, char C, int i, int j)
{
	t_pl *pl = main->pl;
	pl->x = j * 32 + 16;
	pl->y = i * 32 + 16;
	if (C == 'N')
		pl->ang = 270;
	else if (C == 'S')
		pl->ang = 90;
	else if (C == 'W')
		pl->ang = 180;
	else if (C == 'E')
		pl->ang = 0;
	main->map[i][j] = '0';
	return (pl);
}

t_pl    *player_init(t_main *main)
{
	int     i;
	int     j;

	main->pl = malloc(sizeof(t_pl));
	main->pl->flg_trn_l = 0;
	main->pl->flg_trn_r = 0;
	main->pl->flg_move_w = 0;
	main->pl->flg_move_a = 0;
	main->pl->flg_move_s = 0;
	main->pl->flg_move_d = 0;
	i = -1;
	while (main->map[++i])
	{
		j = -1;
		while (main->map[i][++j])
		{
			if (main->map[i][j] != '1' && main->map[i][j] != '0' && \
				main->map[i][j] != ' ')
				return (save_position(main, main->map[i][j], i, j));
		}
	}
	return main->pl;
}