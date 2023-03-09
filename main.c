#include "cub.h"

// Minimap
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

// Minimap
void draw_back(t_main *Main, t_pl *pl, t_img *map)
{
    int             y;
    int             x;
    char            c;
    unsigned int    *dst;

    y = -1;

    while (++y < 500)
    {
        if ((int)pl->y - 250 + y < 0 || ((int)pl->y - 250 + y) / 32 >= Main->map_H)
            continue;
        x = -1;
        while (++x < 500)
        {
            if ((int)pl->x - 250 + x < 0 || ((int)pl->x - 250 + x) / 32 >= Main->map_W[(pl->y - 250 + y) / 32])
                continue;
            c = Main->map[(pl->y - 250 + y) / 32][(pl->x - 250 + x) / 32];
            dst = map->addr + (y * map->line_length + x * (map->bits_per_pixel / 8));
            if (c == '1')
                *dst = WALL_COLOR;
            else if (c == '0')
                *dst = FLOOR_COLOR;
        }
    }
}

// Minimap
void    draw_direction(t_img *map, t_pl *pl)
{
    unsigned int    *ray;
    double          k_x;
    double          k_y;
    size_t          ray_len;

    ray_len = 0;
    while (ray_len < 50)
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

int draw_frame(t_main *Main)
{
    move(Main, Main->pl);
    turn(Main->pl);
    draw_back(Main, Main->pl, &Main->mp->map);
    draw_player(&Main->mp->map, Main->pl);
//	printf("x = %zu, y = %zu, ang = %lf\n", Main->pl->x, Main->pl->y,
//		   Main->pl->ang);
    cast_rays(Main, Main->pl);
    draw_direction(&Main->mp->map, Main->pl);
    mlx_put_image_to_window(Main->mp->mlx, Main->mp->win, Main->mp->vis.img, 0, 0);
    /*mlx_put_image_to_window(Main->mp->mlx, Main->mp->win, Main->mp->map.img,
							 0, 0);*/
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
    while (++i < 768)
    {
        j = -1;
        while (++j < 1024)
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

void    imgs_init(t_main *M)
{
    M->mp->map.img = mlx_new_image(M->mp->mlx, 500, 500);
    M->mp->map.addr = get_data_img(&M->mp->map);
    M->mp->vis.img = mlx_new_image(M->mp->mlx, 1024, 768);
    M->mp->vis.addr = get_data_img(&M->mp->vis);
    M->mp->wall_W.img = mlx_xpm_file_to_image(M->mp->mlx, "texture/WALL_E.xpm", &M->mp->wall_W.w, &M->mp->wall_W.h);
    M->mp->wall_W.addr = get_data_img(&M->mp->wall_W);
}

void game_play(t_main *Main)
{
    Main->mp->mlx = mlx_init();
    Main->mp->win = mlx_new_window(Main->mp->mlx, 1024, 768, "try");
    imgs_init(Main);
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
