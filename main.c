#include "cub.h"

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
    game_play(&Main);
    return (0);
}
