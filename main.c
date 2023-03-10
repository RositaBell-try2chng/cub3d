#include "cub.h"

int draw_frame(t_main *M)
{
    move(M, M->pl);
    turn(M->pl);
    draw_minimap(M);
    cast_rays(M, M->pl);
    mlx_put_image_to_window(M->mp->mlx, M->mp->win, M->mp->vis.img, 0, 0);
    mlx_put_image_to_window(M->mp->mlx, M->mp->win, M->mp->map.img, 0, 0);
    return (0);
}

void parser(t_main *Main)
{
    ssize_t i = 0;
    int  j;
    char    *all_file = malloc(5000);

    i = read(Main->fd, all_file, 5000);
    all_file[i] = 0;
    Main->map = ft_split(all_file, '\n');
    free(all_file);
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
            dst = get_pxl_adr(vis, j, i);
            *dst = GREY_COLOR;
        }
    }
}

void    imgs_init(t_main *M)
{
    M->mp->map.img = mlx_new_image(M->mp->mlx, M_SIZE, M_SIZE);
    M->mp->map.addr = get_data_img(&M->mp->map);
    M->mp->vis.img = mlx_new_image(M->mp->mlx, 1024, 768);
    M->mp->vis.addr = get_data_img(&M->mp->vis);
    M->mp->wall_W.img = mlx_xpm_file_to_image(M->mp->mlx, "texture/WALL_W.xpm", &M->mp->wall_W.w, &M->mp->wall_W.h);
    M->mp->wall_W.addr = get_data_img(&M->mp->wall_W);
    M->mp->wall_E.img = mlx_xpm_file_to_image(M->mp->mlx, "texture/WALL_E.xpm", &M->mp->wall_E.w, &M->mp->wall_E.h);
    M->mp->wall_E.addr = get_data_img(&M->mp->wall_E);
    M->mp->wall_N.img = mlx_xpm_file_to_image(M->mp->mlx, "texture/WALL_N.xpm", &M->mp->wall_N.w, &M->mp->wall_N.h);
    M->mp->wall_N.addr = get_data_img(&M->mp->wall_N);
    M->mp->wall_S.img = mlx_xpm_file_to_image(M->mp->mlx, "texture/WALL_S.xpm", &M->mp->wall_S.w, &M->mp->wall_S.h);
    M->mp->wall_S.addr = get_data_img(&M->mp->wall_S);
}

void game_play(t_main *Main)
{
    Main->mp->mlx = mlx_init();
    Main->mp->win = mlx_new_window(Main->mp->mlx, 1024, 768, "cub3d");
    imgs_init(Main);
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
