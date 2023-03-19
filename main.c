/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbell <rbell@gmail.com>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:46:42 by rbell             #+#    #+#             */
/*   Updated: 2023/03/19 12:46:42 by rbell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"
#include "parser/cub_parser.h"
#include "parser/mem.h"

// Perhaps: endianness?
int	main(int argc, char **argv)
{
	t_main		main;
	int			i;
	t_cub_conf	conf;

	if (argc != 2)
		return (write(2, "wrong\n", 6));
	main.map = NULL;
	main.mp = cub_malloc_or_die(sizeof(t_mlx));
	conf = cub_parse(argv[1]);
	main.map = conf.lines;
	main.map_h = conf.lines_length;
	main.map_w = cub_malloc_or_die(main.map_h * sizeof(int));
	i = -1;
	while (++i < conf.lines_length)
		main.map_w[i] = cub_strlen(conf.lines[i]);
	main.path_east = conf.path_east;
	main.path_north = conf.path_north;
	main.path_west = conf.path_west;
	main.path_south = conf.path_south;
	main.floor_color = conf.floor_red * 256 * 256 + \
			conf.floor_green * 256 + \
			conf.floor_blue;
	main.ceiling_color = conf.ceiling_red * 256 * 256 + \
						conf.ceiling_green * 256 + conf.ceiling_blue;
	game_play(&main);
}
