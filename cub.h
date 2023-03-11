#ifndef CUB_H
# define CUB_H

# include "mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <limits.h>

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
# define GREY_COLOR  0x00808080

//vision colors
# define WALL_N 0x0000FFFF
# define WALL_S 0x00FFFF00
# define WALL_E 0x00FF00FF
# define WALL_W 0x00FFFFFF
# define UP_COLOR 0x007FC7FF - 0x00232323
# define DOWN_COLOR 0x00278E2A - 0x00232323

typedef struct	s_player_data
{
	double			x;
	double			y;
    double          ang;
    char            flg_trn_r;
    char            flg_trn_l;
    char            flg_move_w;
    char            flg_move_a;
    char            flg_move_s;
    char            flg_move_d;
} t_pl;

typedef struct s_image
{
    void	*img;
    void	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
    int		h; //высота текстуры
    int		w; //ширина текстуры
} t_img;

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    t_img   map;
    t_img   vis;
    //для текстур стен
    t_img	wall_N;
    t_img	wall_S;
    t_img	wall_E;
    t_img	wall_W;
} t_mlx;

typedef struct s_main
{
    t_mlx   *mp;
    char    **map;
    int     map_H;
    int     map_W[100];
    int     fd;
    t_pl    *pl;
} t_main;

typedef	struct	s_hit_values
{
	//x y пересечения
	double	X_y;
	double	Y_x;
	//флаг стенки с которой столкнулись X/Y
	char	flg_wall;
	//ray_ang/len/cnt
	double	ang;
	double	len;
	int		cnt;
	//pointer to wall img
	t_img	*side;
	//pl values
	double	pl_x;
	double	pl_y;
} t_hit;

char	**ft_split(char const *s, char c);
void	game_play(t_main *Main);
int		draw_frame(t_main *Main);
void	parser(t_main *Main);
int		ft_red_cross(t_main *Main);
int		ft_press(int key, t_main *Main);
int		ft_release(int key, t_main *Main);
t_pl	*player_init(t_main *Main);
t_pl	*save_position(t_main *Main, char C, int i, int j);

//move
void	move(t_main *Main, t_pl *pl);
void    turn(t_pl *pl);

//raycast
void    cast_rays(t_main *M, t_pl *pl);
double  math_ray_len(t_main *M, t_hit *hit, double ang);
double  math_need_len(double real, double ang);

//cast_func
double	cast_horisontal(t_main *M, t_hit *hit, double ang);
double	cast_vertical(t_main *M, t_hit *hit, double ang);
double	cast_right_down(t_main *M, t_hit *hit);
double	cast_left_down(t_main *M, t_hit *hit);
double	cast_left_up(t_main *M, t_hit *hit);
double	cast_right_up(t_main *M, t_hit *hit);

//cast_utils
char	check_correct(t_main *M, double x, double y, char *flg);
char	check_wall(t_main *M, double x, double y);

//draws
void    draw_vis(t_main *M, t_hit *hit);

//draws_utils
unsigned int	get_pxl(double wall_h, t_hit *hit, int h);
unsigned int	*get_pxl_adr(t_img *img, int x, int y);

//draw minimap
void	draw_minimap(t_main *M);
char	check_border_minimap(t_main *M, int p, int c, int flg);

//common_utils
char	get_map_char(char **map, double y, double x);
#endif
