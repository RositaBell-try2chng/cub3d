#include "parser.h"

#include <unistd.h>
#include <stdlib.h>

int cub_main_test(char *path) {
	t_cub_conf conf = cub_parse(path);

	t_cub_line_list *line_list_ptr = conf.lines;

	{ t_cub_line_list tmp_line;
	for (
		t_cub_line_list *curr_line_ptr = line_list_ptr;
		curr_line_ptr != 0;
		curr_line_ptr = curr_line_ptr->next
	) {
		/* printf(
			"length: %d\n",
			curr_line_ptr->length
		); fflush(stdout); */
		{ t_cub_char_list tmp_list;
		for (
			t_cub_char_list *curr_char_ptr =
				curr_line_ptr->value;
			curr_char_ptr != 0;
			curr_char_ptr = curr_char_ptr->next
		) {
			cub_write1loop_or_die(
				STDOUT_FILENO,
				curr_char_ptr->value
			);
			tmp_list = *curr_char_ptr;
			free(curr_char_ptr);
			curr_char_ptr = &tmp_list;
		} }
		cub_write1loop_or_die(
			STDOUT_FILENO,
			'\n'
		);
		tmp_line = *curr_line_ptr;
		free(curr_line_ptr);
		curr_line_ptr = &tmp_line;
	} }
}

int main(int argc, char **argv) {
	cub_main_test(argv[1]);
}
