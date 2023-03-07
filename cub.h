#ifndef CUB_H
# define CUB_H

// # include <X11/X.h> // Seems to be working without this
# include <X11/keysym.h>

# include "mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <limits.h>

# define ESC XK_Escape
# define W XK_w
# define A XK_a
# define S XK_s
# define D XK_d
# define RIGHT_ARROW XK_Right
# define LEFT_ARROW XK_Left

# define PI 3.14159265

//minimap colors
// ORGB opaqueness
# define WALL_COLOR 0x800000FF
//# define VOID_COLOR 0xFFFFFFFF
# define FLOOR_COLOR 0x80FFFFFF
# define PL_COLOR 0x8000FF00
# define RAY_COLOR 0x80FF0000
# define BLACK_COLOR 0x00000000
# define GREY_COLOR  0x00808080
# define SHADOW_COLOR 0x00404040

//vision colors
# define WALL_N 0x0000FFFF
# define WALL_S 0x00FFFF00
# define WALL_E 0x00FF00FF
# define WALL_W 0x00FFFFFF
# define UP_COLOR 0x007FC7FF - 0x00232323
# define DOWN_COLOR 0x00278E2A - 0x00232323

typedef struct	s_player_data
{
    size_t			x;
    size_t			y;
    double          ang;
    char            flg_trn_r;
    char            flg_trn_l;
    char            flg_move_w;
    char            flg_move_a;
    char            flg_move_s;
    char            flg_move_d;
	double          rays_len[1024];
    double          rays_ang[1024];
    unsigned int    wall_color[1024];
} t_pl;

typedef struct s_image
{
    void	*img;
    void	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
} t_img;

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    t_img   map;
    t_img   vis;
} t_mlx;

typedef struct s_main
{
    t_mlx   *mp;
    char    **map;
    int     map_H;
    int     map_W[50];
    int     fd;
    t_pl    *pl;
} t_main;

char	**ft_split(char const *s, char c);
void	game_play(t_main *Main);
int		draw_frame(t_main *Main);
void	parser(t_main *Main);
int		ft_red_cross(t_main *Main);
int		ft_press(int key, t_main *Main);
int		ft_release(int key, t_main *Main);
t_pl	*player_init(t_main *Main);
t_pl	*save_position(t_main *Main, char C, int i, int j);
void	turn(t_pl *pl);

//move
void	move(t_main *Main, t_pl *pl);
void	move_frd(t_main *Main, t_pl *pl, double ang, int speed);
int		check_walls_x(char **map, int x, int y, double one_speed);
int		check_walls_y(char **map, int x, int y, double one_speed);

//raycast
void    cast_rays(t_main *M, t_pl *pl);
double  math_ray_len(t_main *M, t_pl *pl, int cnt, double ang);
void	math_ray_len1(t_main *M, t_pl *pl, int cnt);
double  math_need_len(double real, double ang);

//cast_func
double	cast_horisontal(t_main *M, t_pl *pl, int cnt, double ang);
double	cast_vertical(t_main *M, t_pl *pl, int cnt, double ang);
double	cast_right_down(t_main *M, t_pl *pl, int cnt);
double	cast_left_down(t_main *M, t_pl *pl, int cnt);
double	cast_left_up(t_main *M, t_pl *pl, int cnt);
double	cast_right_up(t_main *M, t_pl *pl, int cnt);

//cast_utils
char	check_correct(t_main *M, double x, double y, char *flg);
char	check_wall(t_main *M, double x, double y);
#endif
