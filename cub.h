/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <rbell@gmail.com>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:46:42 by rbell             #+#    #+#             */
/*   Updated: 2023/03/19 12:46:42 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB_H
# define CUB_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <limits.h>
# include <signal.h>

# define CUB_PLATFORM_MACOS 0
# define CUB_PLATFORM_LINUX 1

# if CUB_PLATFORM == CUB_PLATFORM_MACOS
#  include "cub_macos.h"
# elif CUB_PLATFORM == CUB_PLATFORM_LINUX
#  include "cub_linux.h"
# endif

# define PI 3.14159265

//magic numbers
# define SCALE 32

//minimap size
# define M_SIZE 300
# define M_HALF 150

//minimap colors
// ORGB opaqueness
# define WALL_COLOR 0x800000FF
# define FLOOR_COLOR 0x80FFFFFF
# define PL_COLOR 0x8000FF00
# define RAY_COLOR 0x80FF0000
# define VOID_COLOR 0xFFFFFFFF

typedef struct s_player_data
{
	double	x;
	double	y;
	double	ang;
	char	flg_trn_r;
	char	flg_trn_l;
	char	flg_move_w;
	char	flg_move_a;
	char	flg_move_s;
	char	flg_move_d;
}	t_pl;

typedef struct s_image
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		h;
	int		w;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	vis;
	t_img	wall_n;
	t_img	wall_s;
	t_img	wall_e;
	t_img	wall_w;
	t_img	map;
	t_img	rock[16];
}	t_mlx;

typedef struct s_main
{
	t_mlx			*mp;
	char			**map;
	int				map_h;
	int				*map_w;
	int				fd;
	t_pl			*pl;
	pid_t			pid;
	char			*path_north;
	char			*path_south;
	char			*path_east;
	char			*path_west;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}	t_main;

typedef struct s_hit_values
{
	double	x_y;
	double	y_x;
	char	flg_wall;
	double	ang;
	double	len;
	int		cnt;
	t_img	*side;
	double	pl_x;
	double	pl_y;
	double	pl_ang;
}	t_hit;

typedef struct s_move
{
	char	**map;
	t_pl	*pl;
	double	ang;
	int		speed;
}	t_move;

//init
t_pl			*player_init(t_main *main);
void			imgs_init(t_main *m);

//game_play
void			game_play(t_main *m);
int				draw_frame(t_main *m);

//hooks
int				ft_red_cross(t_main *m);
int				ft_press(int key, t_main *m);
int				ft_release(int key, t_main *m);

//move
void			moves(t_main *m, t_pl *pl);

//move_utils
char			check_walls(char **map, double x, double y);
void			move_cnt_recursive(t_move *mv, char flg, char step);
void			move_cnt(t_main *m, t_pl *pl, double ang, int speed);
int				define_speed_ang(t_pl *pl, double *p_ang);

//raycast
void			cast_rays(t_main *m, t_pl *pl);
double			math_ray_len(t_main *m, t_hit *hit, double ang);
double			cast_horisontal(t_main *m, t_hit *hit, double ang);
double			cast_vertical(t_main *m, t_hit *hit, double ang);
double			cast_right_down(t_main *m, t_hit *hit);
double			cast_left_down(t_main *m, t_hit *hit);
double			cast_left_up(t_main *m, t_hit *hit);
double			cast_right_up(t_main *m, t_hit *hit);

//cast_utils
char			check_correct(t_main *m, double x, double y, char *flg);
char			check_wall(t_main *m, double x, double y);

//draws
void			draw_vis(t_main *m, t_hit *hit);
void			drawers(t_main *m, t_pl *pl);
void			puts_img(void *mlx, void *win, t_mlx *mp);

//draws_utils
unsigned int	get_pxl(double wall_h, t_hit *hit, int h);
unsigned int	*get_pxl_adr(t_img *img, int x, int y);

//common_utils
char			get_map_char(char **map, double y, double x);
void			init_error_exit(t_main *m, char flg);
char			*get_data_img(t_img *img);
//draw minimap
void			draw_minimap(t_main *m);
char			check_border_minimap(t_main *m, int p, int c, int flg);
void			draw_full_back(t_img *map, int color);
void			draw_direction(t_img *map, t_pl *pl, int k);
void			draw_no_walls_back(t_main *M, t_pl *pl, t_img *map);
void			draw_player(t_img *map);
//music
void			start_music(t_main *m);
#endif
