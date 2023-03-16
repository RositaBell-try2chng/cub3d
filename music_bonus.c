#include "cub.h"

static void	signal_handler(int sig)
{
	if (sig != SIGKILL)
		return ;
	exit(0);
}

static void	music_turn_on()
{
	while (1)
		system("afplay ./rock/doom.m4a");
}

static void	free_resourses(t_main *m)
{
	int	i;

	i = 0;
	free(m->pl);
	while (m->map && m->map[i])
		free(m->map[i++]);
	mlx_destroy_image(m->mp->mlx, m->mp->vis.img);
	mlx_destroy_image(m->mp->mlx, m->mp->map.img);
	mlx_destroy_image(m->mp->mlx, m->mp->wall_w.img);
	mlx_destroy_image(m->mp->mlx, m->mp->wall_e.img);
	mlx_destroy_image(m->mp->mlx, m->mp->wall_n.img);
	mlx_destroy_image(m->mp->mlx, m->mp->wall_s.img);
	free(m->mp);
	free(m->map);
}

void	start_music(t_main *m)
{
	static char	c;

	if (c)
		return ;
	m->pid = fork();
	if (m->pid == 0)
	{
		signal(SIGKILL, signal_handler);
		free_resourses(m);
		music_turn_on();
	}
	else if (m->pid < 0)
		init_error_exit(m, 5);
	c = 1;
}