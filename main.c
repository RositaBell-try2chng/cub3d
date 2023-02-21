#include "cub.h"

void    draw_player(t_img *map, t_pl *pl)
{
    int             i;
    int             j;
    unsigned int    *dst;
    (void)pl;

    i = -1;
    while (++i < 6)
    {
        j = -1;
        while (++j < 6)
        {
            dst = map->addr + ((i + 249 - 2) * map->line_length + (j + 249 - 2) * (map->bits_per_pixel / 8));
            *dst = PL_COLOR;
        }
    }
}

void draw_back(t_main *Main, t_pl *pl, t_img *map)
{
    int             y;
    int             x;
    char            c;
    unsigned int    *dst;

    y = -1;

    while (++y < 500)
    {
        if ((int)pl->y - 250 + y < 0 || ((int)pl->y - 250 + y) / 48 >= Main->map_H)
            continue;
        x = -1;
        while (++x < 500)
        {
            if ((int)pl->x - 250 + x < 0 || ((int)pl->x - 250 + x) / 48 >= Main->map_W[(pl->y - 250 + y) / 48])
                continue;
            c = Main->map[(pl->y - 250 + y) / 48][(pl->x - 250 + x) / 48];
            dst = map->addr + (y * map->line_length + x * (map->bits_per_pixel / 8));
            if (c == '1')
                *dst = WALL_COLOR;//set_wall_color(Main, Main->pl, pl->y - 250 + y, pl->x - 250 + x);
            else if (c == '0')
                *dst = FLOOR_COLOR;
        }
    }
}

unsigned int    set_color_dst(int y, t_pl *pl, int cnt)
{
    if (y < 50)
        return (UP_COLOR);
    if (y > 1150)
        return (DOWN_COLOR);
    if (y < 800)
    {
        if ((y - 51) / pl->rays_len[cnt] >= 2)
            return (pl->wall_color[cnt]);
        return (UP_COLOR);
    }
    else
    {
        if ((1200 - (y + 30)) / pl->rays_len[cnt] >= 1)
            return (pl->wall_color[cnt]);
        return (DOWN_COLOR);
    }
}

//draw_vis(&M->mp->vis, pl, cnt, cnt * (M->mp->vis.bits_per_pixel / 8));
void    draw_vis(t_img *vis, t_pl *pl, int cnt, size_t off_x)
{
    int             y;
    unsigned int    *dst;
    unsigned int    color_dst;

    y = 0;
    while (y < 1200)
    {
        color_dst = set_color_dst(y, pl, cnt);
        dst = vis->addr + (y) * vis->line_length + off_x;
        *dst = color_dst;
        y++;
    }
}

void    draw_rays(t_img *map, t_pl *pl)
{
    unsigned int    *ray;
    double          k_x;
    double          k_y;
    size_t          ray_len;

    ray_len = 0;
    while (ray_len < 50) //&& (cnt == 0.0 || cnt >= 90.0 - (double)(90.0 / 1600.0)))
    {
        k_x = ray_len * cos(pl->ang * PI / 180);
        k_y = ray_len * sin(pl->ang * PI / 180);
        ray = map->addr + (((int) k_y + 249) * map->line_length + ((int) k_x + 249) * (map->bits_per_pixel / 8));
        if (*ray == WALL_COLOR)
            break;
        else
            *ray = RAY_COLOR;
        ray_len++;
    }
}

int check_walls_x(char **map, int x, int y, double one_speed)
{
    int tmp;
    int cnt;

    cnt = -1;
    while (++cnt < 4)
    {
        tmp = x - (int) (cnt * one_speed);
        if (map[(y - 1) / 48][(tmp - 3) / 48] != '1' && map[(y - 1) / 48][(tmp + 1) / 48] != '1' && \
            map[(y + 1) / 48][(tmp + 1) / 48] != '1' && map[(y + 1) / 48][(tmp - 3) / 48] != '1')
            return (tmp);
    }
    return (x - (int)(4 * one_speed));
}

int check_walls_y(char **map, int x, int y, double one_speed)
{
    int tmp;
    int cnt;

    cnt = -1;
    while (++cnt < 4)
    {
        tmp = y - (int) (cnt * one_speed);
        if (map[(tmp - 3) / 48][(x - 1) / 48] != '1' && map[(tmp - 3) / 48][(x + 1) / 48] != '1' && \
            map[(tmp + 1) / 48][(x + 1) / 48] != '1' && map[(tmp + 1) / 48][(x - 1) / 48] != '1')
            return (tmp);
    }
    return (y - (int)(4 * one_speed));
}

void    move_frd(t_main *Main, t_pl *pl, double ang, int speed) {
    int x;
    int y;

    x = (int) pl->x + (int) (4 * speed * cos((ang * PI) / 180));
    y = (int) pl->y + (int) (4 * speed * sin((ang * PI) / 180));
    (void)Main;
    if (ang > 315.0 || ang <= 45 || (ang >= 135.0 && ang < 225.0))
    {
        y = check_walls_y(Main->map, x, y, speed * sin((ang * PI) / 180));
        x = check_walls_x(Main->map, x, y, speed * cos((ang * PI) / 180));
    }
    else
    {
        x = check_walls_x(Main->map, x, y, speed * cos((ang * PI) / 180));
        y = check_walls_y(Main->map, x, y, speed * sin((ang * PI) / 180));
    }
    pl->y = y;
    pl->x = x;
}
void    move(t_main *Main, t_pl *pl)
{
    (void)Main;
    if (pl->flg_move_w == 1 && pl->flg_move_s == 0)
        move_frd(Main, pl, pl->ang, 1);
    else if (pl->flg_move_w == 0 && pl->flg_move_s == 1)
        move_frd(Main, pl, pl->ang, -1);
    if (pl->flg_move_a == 1 && pl->flg_move_d == 0)
        move_frd(Main, pl, pl->ang + 90.0, -1);
    else if (pl->flg_move_a == 0 && pl->flg_move_d == 1)
        move_frd(Main, pl, pl->ang + 90.0, 1);
}

unsigned int set_wall_color(t_main *M, t_pl *pl, size_t y, size_t x)
{
    char flg_x = 0; //0 - norm, -1 - no left_check, 1 - no right_check
    char flg_y = 0; //0 - norm, -1 - no up_check, 1 - no down_check

    if ((int)y / 48 - 1 < 0 || (int)x / 48 >= M->map_W[y / 48 - 1])
        flg_y = -1;
    if ((int)x / 48 - 1 < 0)
        flg_x = -1;
    if ((int)y / 48 + 1 >= M->map_H || (int)x / 48 >= M->map_W[y / 48 + 1])
        flg_y = 1;
    if ((int)x / 48 + 1 >= M->map_W[y / 48])
        flg_x = 1;
    if (x % 48 == 0 && y % 48 == 0)
    {
        if ((flg_x >= 0) && (M->map[y / 48][x / 48 - 1] == '1'))
            return (WALL_N);
        if ((flg_y >= 0) && (M->map[y / 48 - 1][x / 48] == '1'))
            return (WALL_W);
        if (pl->x >= x || (pl->x <= x && pl->y <= y && pl->ang > 45))
            return (WALL_N);
        if (pl->y >= y || (pl->x <= x && pl->y < y && pl->ang <= 45))
            return (WALL_W);
    }
    else if (x % 48 == 0 && (y + 1) % 48 == 0)
    {
        if ((flg_x >= 0) && (M->map[y / 48][x / 48 - 1] == '1'))
            return (WALL_S);
        if ((flg_y <= 0) && (M->map[y / 48 + 1][x / 48] == '1'))
            return (WALL_W);
        if (pl->x >= x || (pl->x < x && pl->y > y && pl->ang < 315))
            return (WALL_S);
        if (pl->y <= y || (pl->x < x && pl->y > y && pl->ang >= 315)) {
            return (WALL_W);
        }
    }
    else if (y % 48 == 0 && (x + 1) % 48 == 0)
    {

        if ((flg_x <= 0) && (M->map[y / 48][x / 48 + 1] == '1'))
            return (WALL_N);
        if ((flg_y >= 0) && (M->map[y / 48 - 1][x / 48] == '1'))
            return (WALL_E);
        if (pl->x <= x || (pl->x > x && pl->y < y && pl->ang < 135))
            return (WALL_N);
        if (pl->y >= y || (pl->x > x && pl->y < y && pl->ang >= 135))
            return (WALL_E);
    }
    else if ((x + 1) % 48 == 0 && (y + 1) % 48 == 0)
    {
        if ((flg_x <= 0) && (M->map[y / 48][x / 48 + 1] == '1'))
            return (WALL_S);
        if ((flg_y <= 0) && (M->map[y / 48 + 1][x / 48] == '1'))
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
    if ((r_x - 0) % 48 == 0 && r_y % 48 != 0 && (r_y - 1) % 48 != 0)
        return (WALL_W);
    if ((r_x - 1) % 48 == 0 && r_y % 48 != 0 && (r_y - 1) % 48 != 0)
        return (WALL_E);
    if ((r_y - 0) % 48 == 0 && r_x % 48 != 0 && (r_x - 1) % 48 != 0)
        return (WALL_N);
    if ((r_y - 1) % 48 == 0 && r_x % 48 != 0 && (r_x - 1) % 48 != 0)
        return (WALL_S);
    return (set_wall_color(M, pl, r_y, r_x));
}

size_t  math_need_len(size_t real, double ang)
{
    if (ang < 0.0)
        ang *= -1;
    return (real * sin((90 - ang) * PI / 180));
}

void  math_ray_len(t_main *M, t_pl *pl, int cnt)
{
    int r_x;
    int r_y;
    int flg_wall;

    flg_wall = 0;
    while (!flg_wall)
    {
        r_x = pl->x + pl->rays_len[cnt] * cos(pl->rays_ang[cnt] * PI / 180.0);
        r_y = pl->y + pl->rays_len[cnt] * sin(pl->rays_ang[cnt] * PI / 180.0);
//        if (r_y < 0 || r_y / 48 >= M->map_H || r_x < 0 || r_x / 48 >= M->map_W[r_y / 48])
//            break;
        if (M->map[r_y / 48][r_x / 48] == '1')
            flg_wall = 1;
        else
            pl->rays_len[cnt]++;
    }
    pl->rays_len[cnt] = math_need_len(pl->rays_len[cnt], pl->ang - pl->rays_ang[cnt]);
    pl->wall_color[cnt] = set_wall_color(M, pl, r_y, r_x);
}

void    cast_rays(t_main *M, t_pl *pl)
{
    int     cnt;

    cnt = -1;
    while (++cnt < 1600)
    {
        pl->rays_ang[cnt] = (pl->ang + ((double)cnt * 90.0 / 1600.0) - 45);
        pl->rays_len[cnt] = 0;
        math_ray_len(M, pl, cnt);
        draw_vis(&M->mp->vis, pl, cnt, cnt * (M->mp->vis.bits_per_pixel / 8));
    }
}

int draw_frame(t_main *Main)
{
    move(Main, Main->pl);
    turn(Main->pl);
    draw_back(Main, Main->pl, &Main->mp->map);
    draw_player(&Main->mp->map, Main->pl);
    cast_rays(Main, Main->pl);
    draw_rays(&Main->mp->map, Main->pl);
    mlx_put_image_to_window(Main->mp->mlx, Main->mp->win, Main->mp->vis.img, 0, 0);
    mlx_put_image_to_window(Main->mp->mlx, Main->mp->win, Main->mp->map.img, 0, 0);
    return (0);
}

void parser(t_main *Main)
{
    ssize_t i = 0;
    int  j;
    char    all_file[1000];

    i = read(Main->fd, all_file, 1000);
    all_file[i] = 0;
    Main->map = ft_split(all_file, '\n');
    i = -1;
    while (Main->map[++i])
    {
        j = 0;
        while (Main->map[i][j])
            j++;
        Main->map_W[i] = j;
    }
    Main->map_H = (int)i;
}

char *get_data_img(t_img *img)
{
    char *res;

    res = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    return (res);
}

void    draw_full_vis(t_img *vis)
{
    size_t          i;
    size_t          j;
    unsigned int    *dst;

    i = -1;
    while (++i < 1200)
    {
        j = -1;
        while (++j < 1600)
        {
            dst = vis->addr + (i * vis->line_length + j * (vis->bits_per_pixel / 8)) ;
            *dst = GREY_COLOR;
        }
    }
}

void draw_full_back(t_img *map, int color)
{
    int             i;
    int             j;
    unsigned int    *dst;

    i = -1;
    while (++i < 500)
    {
        j = -1;
        while (++j < 500)
        {
            dst = map->addr + i * map->line_length + j * (map->bits_per_pixel / 8);
            *dst = color;
        }
    }
}

void game_play(t_main *Main)
{
    Main->mp->mlx = mlx_init();
    Main->mp->win = mlx_new_window(Main->mp->mlx, 1600, 1200, "try");
    Main->mp->map.img = mlx_new_image(Main->mp->mlx, 500, 500);
    Main->mp->map.addr = get_data_img(&Main->mp->map);
    Main->mp->vis.img = mlx_new_image(Main->mp->mlx, 1600, 1200);
    Main->mp->vis.addr = get_data_img(&Main->mp->vis);
    draw_full_back(&Main->mp->map, WALL_COLOR);
    draw_full_vis(&Main->mp->vis);
    mlx_hook(Main->mp->win, 2, 1L << 0, ft_press, Main);
    mlx_hook(Main->mp->win, 3, 1L << 1, ft_release, Main);
    mlx_hook(Main->mp->win, 17, 1L << 17, ft_red_cross, Main);
    mlx_loop_hook(Main->mp->mlx, draw_frame, Main);
    mlx_loop(Main->mp->mlx);
}

t_pl *save_position(t_main *Main, char C, int i, int j)
{
    t_pl *pl = Main->pl;
    pl->x = j * 48 + 24;
    pl->y = i * 48 + 24;
    if (C == 'N')
        pl->ang = 270;
    else if (C == 'S')
        pl->ang = 90;
    else if (C == 'W')
        pl->ang = 180;
    else if (C == 'E')
        pl->ang = 0;
    Main->map[i][j] = '0';
    return (pl);
}

t_pl    *player_init(t_main *Main)
{
    int     i;
    int     j;

    Main->pl = malloc(sizeof(t_pl));
    Main->pl->flg_trn_l = 0;
    Main->pl->flg_trn_r = 0;
    Main->pl->flg_move_w = 0;
    Main->pl->flg_move_a = 0;
    Main->pl->flg_move_s = 0;
    Main->pl->flg_move_d = 0;
    i = -1;
    while (Main->map[++i])
    {
        j = -1;
        while (Main->map[i][++j])
        {
            if (Main->map[i][j] != '1' && Main->map[i][j] != '0' && Main->map[i][j] != ' ') {
                return (save_position(Main, Main->map[i][j], i, j));
            }
        }
    }
    return Main->pl;
}

int	main(int argc, char **argv)
{
    t_main  Main;

    if (argc != 2)
        return (write(2, "wrong\n", 6));
    Main.map = NULL;
    Main.fd = open(argv[1], O_RDONLY);
    Main.mp = malloc(sizeof(t_mlx));
    if (!Main.mp)
        return (printf("bad alloc\n"));
    parser(&Main);
    close(Main.fd);
    Main.pl = player_init(&Main);
    game_play(&Main);
    return (0);
}
