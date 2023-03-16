#include "cub.h"

char	get_map_char(char **map, double y, double x)
{
	int		m_x;
	int		m_y;

	m_y = (int)(y / 32);
	m_x = (int)(x / 32);
	return (map[m_y][m_x]);
}

void	init_error_exit(t_main *m, char flg)
{
	int	i;

	free(m->pl);
	i = 0;
	while (m->map && m->map[i])
		free(m->map[i++]);
	free(m->map);
	if (flg == 0 || flg == 1)
		return ;
	mlx_destroy_image(m->mp->mlx, m->mp->vis.img);
	if (m->mp->wall_w.img)
		mlx_destroy_image(m->mp->mlx, m->mp->wall_w.img);
	if (m->mp->wall_e.img)
		mlx_destroy_image(m->mp->mlx, m->mp->wall_e.img);
	if (m->mp->wall_n.img)
		mlx_destroy_image(m->mp->mlx, m->mp->wall_n.img);
	if (m->mp->wall_s.img)
		mlx_destroy_image(m->mp->mlx, m->mp->wall_s.img);
	if (flg != 5)
		write(2, "Error: init_error\n", 19);
	else
		write(2, "Error: fork_error\n", 19);
	exit(1);
}

char	*get_data_img(t_img *img)
{
	char *res;

	res = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	return (res);
}