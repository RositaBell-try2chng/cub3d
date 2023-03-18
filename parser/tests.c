#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "cub_parser.h"

#include "cub_parser_private.h"

#define CUB_PRINTF(fmt, wat) printf(# wat ": " "%" # fmt "\n", wat); fflush(stdout)

void cub_main_test(char *path) {

	t_cub_conf conf = cub_parse(path);

	CUB_PRINTF(d, conf.floor_red);
	CUB_PRINTF(d, conf.floor_green);
	CUB_PRINTF(d, conf.floor_blue);
	CUB_PRINTF(d, conf.ceiling_red);
	CUB_PRINTF(d, conf.ceiling_green);
	CUB_PRINTF(d, conf.ceiling_blue);
	CUB_PRINTF(s, conf.path_north);
	CUB_PRINTF(s, conf.path_south);
	CUB_PRINTF(s, conf.path_west);
	CUB_PRINTF(s, conf.path_east);
	printf("\n");

	CUB_PRINTF(d, conf.lines_length);
	for (int i = 0; i < conf.lines_length; i++) {
		char *line = conf.lines[i];
		for (
			char *tmp = line;
			(*tmp) != 0;
			tmp++
		) {
			printf("%c", *tmp);
		}
		free(line);
		printf("\n");
	}
	free(conf.lines[conf.lines_length]); // For zero?
	free(conf.lines);
	{
	char *pathsz [] = {
		conf.path_north,
		conf.path_south,
		conf.path_east,
		conf.path_west,
		0
	};
	for (
		char **path_ptr = pathsz;
		*path_ptr != 0;
		path_ptr++
	) free(*path_ptr);
	}
}

int main(int argc, char **argv) {
	cub_main_test(argv[1]);
//	for (;;)
//		;

}
