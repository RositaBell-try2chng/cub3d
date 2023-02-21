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

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define PI 3.14159265
//359
# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define WALL_COLOR 0x800000FF
# define VOID_COLOR 0xFFFFFFFF
# define FLOOR_COLOR 0x80FFFFFF
# define PL_COLOR 0x8000FF00
# define RAY_COLOR 0x80FF0000
# define BLACK_COLOR 0x00000000
# define GREY_COLOR  0x00808080
# define OFFSET 48 * 3 + 24
# define SHADOW_COLOR 0x00404040

# define WALL_N 0x0000FFFF
# define WALL_S 0x00FFFF00
# define WALL_E 0x00FF00FF
# define WALL_W 0x00FFFFFF

# define UP_COLOR 0x007FC7FF - 0x00232323
# define DOWN_COLOR 0x00278E2A - 0x00232323

typedef struct s_player_data
{
    size_t          x;
    size_t          y;
    double          ang;
    char            flg_trn_r;
    char            flg_trn_l;
    char            flg_move_w;
    char            flg_move_a;
    char            flg_move_s;
    char            flg_move_d;
    size_t          rays_len[1600];
    double          rays_ang[1600];
    unsigned int    wall_color[1600];
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
void    game_play(t_main *Main);
int     draw_frame(t_main *Main);
void    parser(t_main *Main);
int     ft_red_cross(t_main *Main);
int     ft_press(int key, t_main *Main);
int     ft_release(int key, t_main *Main);
t_pl    *player_init(t_main *Main);
t_pl    *save_position(t_main *Main, char C, int i, int j);
void    turn(t_pl *pl);
int     check_walls_x(char **map, int x, int y, double one_speed);
int     check_walls_y(char **map, int x, int y, double one_speed);
#endif