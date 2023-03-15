#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "../cub.h"
#include "parser.h"

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

void write_loop_or_die(int fd, char *s) {
	for (char c = *s; c != 0; c = *++s) {
		write1loop_or_die(fd, c);
	}
}

_Bool are_strings_equal(char *s1, char *s2) {
	while (*s1 && *s2) {
		if (*s1 != *s2)
			return 0;
		s1++; s2++;
	}
	return *s1 == *s2;
}

static void cub_check_extension_or_die(char *name) {
	char c;
	// Parse until on dot
	for (c = *name; c != 0 && c != '.'; c = *++name)
		;
	if (c == 0) {
		write_loop_or_die(
			2,
			"Error\n"
			"cub_check_extension_or_die: "
			"no extension in file name\n"
		);
		exit(1);
	}
	name++;
	if (!are_strings_equal(name, "cub")) {
		write_loop_or_die(
			2,
			"Error\n"
			"cub_check_extension_or_die: "
			"extension is not “cub”\n"
		);
		exit(1);
	}
}

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

t_cub_char_list *cub_fd_to_char_list_ptr(int fd) {
	t_cub_char_list *char_list_ptr = 0;
	while (1) {
		int c = read1_or_die(fd);
		if (c == -1) break;

		t_cub_char_list *tmp_ptr =
			malloc_or_die(sizeof(t_cub_char_list));
		*tmp_ptr = (t_cub_char_list){
			.value = c,
			.next = char_list_ptr,
		};

		char_list_ptr = tmp_ptr;
	}
	// Close here since resource is consumed
	close(fd);
	return char_list_ptr;
}

t_cub_line_list *
cub_char_list_ptr_to_line_list_ptr(t_cub_char_list *char_list_ptr) {
	t_cub_line_list *line_list_ptr = 0;
	while (1) {
		if (char_list_ptr == 0)
			break;
		t_cub_char_list *next_ptr = char_list_ptr->next;

		char c = char_list_ptr->value;

		switch (c) {
		case '\n': {
			t_cub_line_list *tmp_ptr =
				malloc_or_die(sizeof(t_cub_line_list));
			*tmp_ptr = (t_cub_line_list){
				.next = line_list_ptr,
				.value = 0,
				.length = 0,
			};
			line_list_ptr = tmp_ptr;
		} break;
		default: { // Prepend char to curr char_list
			t_cub_char_list *tmp_ptr_2 =
				malloc_or_die(sizeof(t_cub_char_list));

			*tmp_ptr_2 = (t_cub_char_list){
				.next = line_list_ptr->value,
				.value = c,
			};
			line_list_ptr->value = tmp_ptr_2;
			line_list_ptr->length++;
		} break;
		}

		free(char_list_ptr);
		char_list_ptr = next_ptr;
	}
	return line_list_ptr;
}

t_cub_conf cub_parse(char *path) {
	t_cub_conf conf;

	cub_check_extension_or_die(path);
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		perror("Error\ncub_parse");
		exit(1);
	}

	t_cub_char_list *char_list_ptr = cub_fd_to_char_list_ptr(fd);

	t_cub_line_list *line_list_ptr = cub_char_list_ptr_to_line_list_ptr(char_list_ptr);

	conf.lines = line_list_ptr;

	cub_replace_spaces_with_ones(conf.lines);

	cub_check_map_frame_or_die(conf.lines);

	return conf;
}

int cub_check_extension_or_die_test(char *path) {
	cub_check_extension_or_die(path);
}

void cub_replace_spaces_with_ones(t_cub_line_list *lines) {
	for (
		t_cub_line_list *a_line_ptr = lines;
		a_line_ptr != 0;
		a_line_ptr = a_line_ptr->next
	) {
		for (
			t_cub_char_list *a_char_ptr =
				a_line_ptr->value;
			a_char_ptr != 0;
			a_char_ptr = a_char_ptr->next
		) {
			if (a_char_ptr->value == ' ')
				a_char_ptr->value = '1';
		}
	}
}

void error_die(char *message) {
	write_loop_or_die(2, "Error\n");
	write_loop_or_die(2, message);
	write_loop_or_die(2, "\n");
	exit(1);
}

void true_or_error_die(_Bool condition, char *message) {
	if (!condition) {
		error_die(message);
	}
}

void cub_debug_print_map(t_cub_line_list *lines) {
	for (
		t_cub_line_list *a_line_ptr = lines;
		a_line_ptr != 0;
		a_line_ptr = a_line_ptr->next
	) {
		for (
			t_cub_char_list *a_char_ptr =
				a_line_ptr->value;
			a_char_ptr != 0;
			a_char_ptr = a_char_ptr->next
		) {
			write1loop_or_die(
				2,
				a_char_ptr->value
			);
		}
		write1loop_or_die(2, '\n');
	}
}

void cub_check_map_top_or_bottom_or_die(t_cub_char_list *line) {
	while (1) {
		if (line == 0) break;
		true_or_error_die(
			line->value == '1',
			"cub_check_map_top_or_bottom_or_die: "
			"map is not framed "
			"horizontally"
		);
		line = line -> next;
	}
}

void cub_check_map_empty_line_or_die(int length) {
	true_or_error_die(
		length > 0,
		"cub_check_map_left_and_right_or_die: "
		"map line can't be empty because it must be in a frame"
	);
}

static int cub_min(int a, int b) { return a < b ? a : b; }

// Prev might be null
void cub_check_map_left_and_right_or_die(
	t_cub_line_list *prev,
	t_cub_line_list *curr
) {
	_Bool first_column = 1;
	_Bool last_column;
	cub_check_map_empty_line_or_die(curr->length);
	// First line is checked by a different function
	if (prev == 0) return;
	// Everything in range [must_be_walls; ∞) must be '1'
	int must_be_walls = cub_min(curr -> length, prev -> length);
	{
	t_cub_char_list *curr_char_ptr = curr -> value;
	t_cub_char_list *prev_char_ptr = prev -> value;
	while (1) {
		if (curr_char_ptr == 0 || prev_char_ptr == 0) break;
		if (curr_char_ptr -> next == 0)
			true_or_error_die(
				curr_char_ptr -> value == '1',
				"cub_check_map_left_and_right_or_die: "
				"map’s right edge can't be zero"
			);
		if (first_column)
			true_or_error_die(
				curr_char_ptr -> value == '1',
				"cub_check_map_left_and_right_or_die: "
				"map’s left edge can't be zero"
			);
		first_column = 0;
		curr_char_ptr = curr_char_ptr -> next;
		prev_char_ptr = prev_char_ptr -> next;
	}
	t_cub_char_list *must_be_walls_char_ptr =
		curr_char_ptr == 0 ? prev_char_ptr : curr_char_ptr;
	while (must_be_walls_char_ptr) {
		true_or_error_die(
			must_be_walls_char_ptr -> value == '1',
			"cub_check_map_left_and_right_or_die: "
			// Fix me: cliff is a weird word
			"map’s right cliff can't be zero"
		);
		must_be_walls_char_ptr = must_be_walls_char_ptr -> next;
	}
	}
}

void cub_check_map_frame_or_die(t_cub_line_list *lines) {
	_Bool first_row = 1;
	_Bool last_row;
	t_cub_line_list *prev = 0;
	for (
		t_cub_line_list *a_line_ptr = lines;
		a_line_ptr != 0;
		a_line_ptr = a_line_ptr->next
	) {
		last_row = a_line_ptr->next == 0;
		if (first_row || last_row)
			cub_check_map_top_or_bottom_or_die(
				a_line_ptr->value
			);
		cub_check_map_left_and_right_or_die(
			prev,
			a_line_ptr
		);
		first_row = 0;
		prev = a_line_ptr;
	}
}
