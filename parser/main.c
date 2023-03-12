#include "../cub.h"
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

/* static void cub_assert_write(int fd, char c) {
	assert(cub_write(fd, c) != -1);
}

static void cub_assert_write_stdout(char c) {
	cub_assert_write(STDOUT_FILENO, c);
} */

// Takes a file descriptor.
// Returns -1 on failure, 0 on end of file, read character otherwise.
int read1(int fd) {
	int result;
	char c;
	int much_read = read(fd, &c, 1);
	if (much_read == 1)
		result = c;
	else
		result = much_read;
	return result;
}

// Takes a file descriptor.
// Dies on error.
// Returns -1 on end of file, read character otherwise.
int read1_or_die(int fd) {
	int much_read = read1(fd);
	if (much_read == 0)
		return -1;
	if (much_read == -1) {
		perror("Error\nread1_or_die");
		exit(1);
	}
}

void *malloc_or_die(size_t size) {
	void *result = malloc(size);
	if (result == 0) {
		perror("Error\nmalloc_or_die");
		exit(1);
	}
	return result;
}

void write1loop_or_die(int fd, char c) {
	while (1) {
		int much_written = write(fd, &c, 1);
		if (much_written == 1)
			return;
		if (much_written == -1) {
			perror("Error\nwrite1loop_or_die");
			exit(1);
		}
	}
}

void cub_parse(char *path) {
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		perror("Error\ncub_parse");
		exit(1);
	}
	t_cub_char_list *char_list_ptr = 0;
	while (1) {
		int much_read = read1_or_die(fd);
		if (much_read == -1) break;

		t_cub_char_list *tmp_ptr =
			malloc_or_die(sizeof(t_cub_char_list));
		*tmp_ptr = (t_cub_char_list){
			.value = much_read,
			.next = char_list_ptr,
		};

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
					malloc_or_die(sizeof(t_cub_line_list));
				*tmp_ptr = (t_cub_line_list){
					.next = line_list_ptr,
					.value = 0,
					.length = 0,
				};
				line_list_ptr = tmp_ptr;
			break;
			default: // Prepend char to curr char_list
				t_cub_char_list *tmp_ptr_2 =
					malloc_or_die(sizeof(t_cub_char_list));

				*tmp_ptr_2 = (t_cub_char_list){
					.next = line_list_ptr->value,
					.value = c,
				};
				line_list_ptr->value = tmp_ptr_2;
				line_list_ptr->length++;
			break;
			}
		}

		free(char_list_ptr);
		char_list_ptr = next_ptr;
	}
	{ t_cub_line_list tmp_line;
	for (
		t_cub_line_list *curr_line_ptr = line_list_ptr;
		curr_line_ptr != 0;
		curr_line_ptr = curr_line_ptr->next
	) {
		printf(
			"length: %d\n",
			curr_line_ptr->length
		); fflush(stdout);
		{ t_cub_char_list tmp_list;
		for (
			t_cub_char_list *curr_char_ptr =
				curr_line_ptr->value;
			curr_char_ptr != 0;
			curr_char_ptr = curr_char_ptr->next
		) {
			write1loop_or_die(
				STDOUT_FILENO,
				curr_char_ptr->value
			);
			tmp_list = *curr_char_ptr;
			free(curr_char_ptr);
			curr_char_ptr = &tmp_list;
		} }
		write1loop_or_die(
			STDOUT_FILENO,
			'\n'
		);
		tmp_line = *curr_line_ptr;
		free(curr_line_ptr);
		curr_line_ptr = &tmp_line;
	} }
	close(fd);
}

int main(int argc, char **argv) {
	cub_parse(argv[1]);
}
