#include "cub.h"
#include "parser/cub_parser.h"

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

// Fix me: don't repeat yourself
static int cub_strlen(char *input) {
    int result = 0;
    while (*input) {
        input++;
        result++;
    }
    return result;
}

int	main(int argc, char **argv)
{
    t_main  Main;

    if (argc != 2)
        return (write(2, "wrong\n", 6));
    Main.map = NULL;
    Main.mp = malloc(sizeof(t_mlx));
    if (!Main.mp)
        return (printf("bad alloc\n"));

    // Fix me: clean this up
//    Main.fd = open(argv[1], O_RDONLY);
//    parser(&Main);

    t_cub_conf conf = cub_parse(argv[1]);
    Main.map = conf.lines;
    Main.map_H = conf.lines_length;
    // Fix me: make map_W dynamically sized
    for (int i = 0; i < conf.lines_length; i++) {
        Main.map_W[i] = cub_strlen(conf.lines[i]);
    }
    Main.path_east = conf.path_east;
    Main.path_north = conf.path_north;
    Main.path_west = conf.path_west;
    Main.path_south = conf.path_south;

    // Fix me: endianness???
    Main.floor_color =
            conf.floor_red * 256 * 256 +
            conf.floor_green * 256 +
            conf.floor_blue;
    Main.ceiling_color = conf.ceiling_red * 256 * 256 + conf.ceiling_green * 256 + conf.ceiling_blue;

//    close(Main.fd);
    game_play(&Main);
    return (0);
}
