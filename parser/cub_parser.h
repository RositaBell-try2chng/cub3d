#ifndef CUB_PARSER_H
#define CUB_PARSER_H

#include <stddef.h>

// Result of a parse
typedef struct {
	char **lines; // Malloc'ed
	int lines_length;

	// Malloc'ed
	char *path_north;
	char *path_south;
	char *path_east;
	char *path_west;

	_Bool floor_set;
	int floor_red;
	int floor_green;
	int floor_blue;

	_Bool ceiling_set;
	int ceiling_red;
	int ceiling_green;
	int ceiling_blue;
} t_cub_conf;

// Input: path to .cub file
// Output: death or valid conf
t_cub_conf cub_parse(char *path);

#endif
