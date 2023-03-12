#include "../cub.h"
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_cub_char_list {
	char value;
	struct s_cub_char_list *next;
} t_cub_char_list;

typedef struct s_cub_line_list {
	int length;
	t_cub_char_list *value;
	struct s_cub_line_list *next;
} t_cub_line_list;

static int cub_write(int fd, char c) {
	while (1) {
		int much_written = write(fd, &c, 1);
		if (much_written == -1)
			return -1;
		if (much_written == 1)
			return 1;
	}
}

static void cub_assert_write(int fd, char c) {
	assert(cub_write(fd, c) != -1);
}

static void cub_assert_write_stdout(char c) {
	cub_assert_write(STDOUT_FILENO, c);
}

int main(int argc, char **argv) {
	int fd = open(argv[1], O_RDONLY);
	assert(fd != -1);
	char c;
	t_cub_char_list *char_list_ptr = 0;
	while (1) {
		int much_read = read(fd, &c, 1);
		assert(much_read != -1);
		if (much_read == 0)
			break;

		t_cub_char_list *tmp_ptr =
			malloc(sizeof(t_cub_char_list));
		assert(tmp_ptr != 0);
		tmp_ptr->value = c;
		tmp_ptr->next = char_list_ptr;

		char_list_ptr = tmp_ptr;

	}

	/* if (char_list_ptr != 0) {
		cub_assert_write_stdout('"');
		cub_assert_write_stdout(char_list_ptr->value);
		cub_assert_write_stdout('"');
		if (char_list_ptr->next != 0) {
			cub_assert_write_stdout('"');
			cub_assert_write_stdout(
				char_list_ptr->next->value
			);
			cub_assert_write_stdout('"');
		}
	}
	cub_assert_write_stdout('\n'); */

	t_cub_line_list *line_list_ptr = 0;
	// // There is always at least 1 line? What?
	// t_cub_line_list *tmp_ptr = malloc(sizeof(t_cub_line_list));
	// assert(tmp_ptr != 0);
	// tmp_ptr->next = line_list_ptr;
	// tmp_ptr->value = 0;
	// tmp_ptr->length = 0;
	// line_list_ptr = tmp_ptr;
	_Bool ok = 1;
	// One dimension into two dimensions
	while (1) {
		if (char_list_ptr == 0)
			break;
		t_cub_char_list *next_ptr = char_list_ptr->next;

		char c = char_list_ptr->value;

		if (ok) {
			switch (c) {
			case '\n':
				// // Ignore last newline. What?
				// if (next_ptr == 0)
				// 	break;
				t_cub_line_list *tmp_ptr =
					malloc(sizeof(t_cub_line_list));
				if (tmp_ptr == 0) {
					ok = 0;
					break;
				}
				tmp_ptr->next = line_list_ptr;
				tmp_ptr->value = 0;
				tmp_ptr->length = 0;
				line_list_ptr = tmp_ptr;
			break;
			default: // Prepend char to curr char_list
				t_cub_char_list *tmp_ptr_2 =
					malloc(sizeof(t_cub_char_list));
				if (tmp_ptr_2 == 0) {
					ok = 0;
					break;
				}

				tmp_ptr_2->next = line_list_ptr->value;
				tmp_ptr_2->value = c;

				line_list_ptr->value = tmp_ptr_2;
				line_list_ptr->length++;
			break;
			}
		}

		free(char_list_ptr);
		char_list_ptr = next_ptr;
	}
	for (
		t_cub_line_list *curr_line_ptr = line_list_ptr;
		curr_line_ptr != 0;
		curr_line_ptr = curr_line_ptr->next
	) {
		printf(
			"length: %d\n",
			curr_line_ptr->length
		); fflush(stdout);
		for (
			t_cub_char_list *curr_char_ptr =
				curr_line_ptr->value;
			curr_char_ptr != 0;
			curr_char_ptr = curr_char_ptr->next
		) {
			cub_assert_write_stdout(
				curr_char_ptr->value
			);
		}
		cub_assert_write_stdout('\n');
	}
}
