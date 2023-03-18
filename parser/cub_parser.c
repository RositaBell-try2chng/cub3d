#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "../cub.h"

#include "cub_parser.h"

#include "cub_parser_private.h"

// Fix me: use this everywhere
// _Bool is_line_break(char c) { return c == '\n' || c == '\r'; }

void cub_write1loop_or_die(int fd, char c) {
	while (1) {
		int much_written = write(fd, &c, 1);
		if (much_written == 1)
			return;
		if (much_written == -1) {
			perror("Error\ncub_write1loop_or_die");
			exit(1);
		}
	}
}

void cub_write_loop_or_die(int fd, char *s) {
	for (char c = *s; c != 0; c = *++s) {
		cub_write1loop_or_die(fd, c);
	}
}

_Bool cub_are_strings_equal(char *s1, char *s2) {
	while (*s1 && *s2) {
		if (*s1 != *s2)
			return 0;
		s1++; s2++;
	}
	return *s1 == *s2;
}

void cub_check_extension_or_die(char *name) {
	char c;
	// Parse until on dot
	for (c = *name; c != 0 && c != '.'; c = *++name)
		;
	if (c == 0) {
		cub_write_loop_or_die(
			2,
			"Error\n"
			"cub_check_extension_or_die: "
			"no extension in file name\n"
		);
		exit(1);
	}
	name++;
	if (!cub_are_strings_equal(name, "cub")) {
		cub_write_loop_or_die(
			2,
			"Error\n"
			"cub_check_extension_or_die: "
			"extension is not “cub”\n"
		);
		exit(1);
	}
}

int cub_read1(int fd) {
	int result;
	char c;
	int much_read = read(fd, &c, 1);
	if (much_read == 1)
		result = c;
	else
		result = much_read;
	return result;
}

int cub_read1_or_die(int fd) {
	int much_read = cub_read1(fd);
	if (much_read == 0)
		return -1;
	if (much_read == -1) {
		perror("Error\nread1_or_die");
		exit(1);
	}
	return much_read;
}

void *cub_malloc_or_die(size_t size) {
	void *result = malloc(size);
	if (result == 0) {
		perror("Error\ncub_malloc_or_die");
		exit(1);
	}
	return result;
}

t_cub_char_list *cub_fd_to_char_list_ptr_or_die(char first, int fd) {
	t_cub_char_list *char_list_ptr =
		cub_malloc_or_die(sizeof *char_list_ptr);
	*char_list_ptr = (t_cub_char_list){
		.value = first,
		.next = 0,
	};
	while (1) {
		int c = cub_read1_or_die(fd);
		if (c == -1) break;

		t_cub_char_list *tmp_ptr =
			cub_malloc_or_die(sizeof *tmp_ptr);
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
		case '\n':
		case '\r': {
			t_cub_line_list *tmp_line_ptr =
				cub_malloc_or_die(sizeof *tmp_line_ptr);
			*tmp_line_ptr = (t_cub_line_list){
				.next = line_list_ptr,
				.value = 0,
				.length = 0,
			};
			line_list_ptr = tmp_line_ptr;
		} break;
		default: { // Prepend char to curr char_list
			t_cub_char_list *tmp_ptr_2 =
				cub_malloc_or_die(sizeof *tmp_ptr_2);

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

char cub_read_char_or_die(int fd) {
	int result = cub_read1_or_die(fd);
	if (result == -1) {
		cub_error_die(
			"cub_read1_char_or_die: "
			"expected a char, but got end of file"
		);
	}
	return result;
}

char cub_skip_spaces_or_die(int fd) {
	char result = ' ';
	while (result == ' ') {
		result = cub_read_char_or_die(fd);
	}
	return result;
}

char cub_skip_new_lines_or_die(int fd) {
	char result = '\n';
	while (result == '\n' || result == '\r') {
		result = cub_read_char_or_die(fd);
	}
	return result;
}

t_cub_char_list *cub_parse_until_got_new_line_or_die(
	int fd,
	t_cub_char_list *previous
) {
	t_cub_char_list *result = previous;
	while (1) {
		char c = cub_read_char_or_die(fd);
		switch (c) {
		case '\n':
		case '\r':
			return result;
		break;
		default: {
			t_cub_char_list *tmp_ptr =
				cub_malloc_or_die(sizeof *tmp_ptr);
			*tmp_ptr = (t_cub_char_list){
				.value = c,
				.next = result,
			};
			result = tmp_ptr;
		} break;
		}
	}
}

t_cub_char_list *cub_reverse_char_list_or_die(t_cub_char_list *input) {
	t_cub_char_list *output = 0;
	t_cub_char_list tmp_input;
	while (input) {
		t_cub_char_list *tmp_output_ptr =
			cub_malloc_or_die(sizeof *tmp_output_ptr);
		*tmp_output_ptr = (t_cub_char_list){
			.value = input -> value,
			.next = output,
		};
		output = tmp_output_ptr;
		tmp_input = *input;
		free(input);
		input = tmp_input . next;
	}
	return output;
}

int cub_char_list_len(t_cub_char_list *list) {
	int result = 0;
	while (list) {
		result++;
		list = list -> next;
	}
	return result;
}

char *cub_char_list_to_chars_or_die(t_cub_char_list *list) {
	int len = cub_char_list_len(list);
	char *chars = cub_malloc_or_die(len + 1);
	chars[len] = 0;

	{
	t_cub_char_list tmp;
	for (int i = 0; i < len; i++) {
		if (list == 0)
			break;
		chars[i] = list -> value;
		tmp = *list;
		free(list);
		list = &tmp;
		list = list -> next;
	} }
	return chars;
}

char *cub_parse_entry_value_or_die(char first, int fd) {
	if (first == '\n' || first == '\r') {
		cub_error_die(
			"cub_parse_entry_value_or_die: "
			"entry value can't be empty"
		);
	}
	t_cub_char_list *first_char_list_ptr =
		cub_malloc_or_die(sizeof *first_char_list_ptr);
	*first_char_list_ptr = (t_cub_char_list){
		.value = first,
		.next = 0,
	};

	return
		cub_char_list_to_chars_or_die(
			cub_reverse_char_list_or_die(
				cub_parse_until_got_new_line_or_die(
					fd,
					first_char_list_ptr
				)
			)
		);
}

void cub_write_char_list_or_die(int fd, t_cub_char_list *ptr) {
	while (ptr) {
		cub_write1loop_or_die(fd, ptr -> value);
		ptr = ptr -> next;
	}
}

// Assumes ASCII
_Bool cub_is_digit(char c) { return c >= '0' && c <= '9'; }

// Assumes ASCII
int cub_char_to_int(char c) { return c - '0'; }

int cub_validate_color_number_or_die(t_cub_char_list *chars) {
	if (chars -> next == 0) { // One digit
		int result = cub_char_to_int(chars -> value);
		free(chars);
		return result;
	} else if (chars -> next -> next == 0) { // Two digits
		// Digits
		int second = cub_char_to_int(chars -> value);
		int first = cub_char_to_int(chars -> next -> value);
		int result = first * 10 + second;
		free(chars -> next);
		free(chars);
		return result;
	} else if (chars -> next -> next -> next == 0) { // Three digits
		int third = cub_char_to_int(chars -> value);
		int second = cub_char_to_int(chars -> next -> value);
		int first = cub_char_to_int(chars -> next -> next -> value);
		int result = first * 10 * 10 + second * 10 + third;
		free(chars -> next -> next);
		free(chars -> next);
		free(chars);
		cub_true_or_error_die(
			result >= 0 && result < 256,
			"cub_validate_color_number_or_die: "
			"number is too big"
		);
		return result;
	} else {
		cub_write_loop_or_die(
				STDERR_FILENO,
				"cub_validate_color_number_or_die: unreachable"
		);
		exit(2);
	}
}

// void cub_free_char_list_ptrs(t_cub_char_list *input) {
// 	while (input) {
// 		t_cub_char_list *next = input -> next;
// 		free(input);
// 		input = next;
// 	}
// }

int
cub_parse_color_number_or_die(char first, int fd, char *last_out_ptr) {
	t_cub_char_list *result = 0;

	if (!cub_is_digit(first))
		cub_error_die(
			"cub_parse_color_number_or_die: "
			"not parsing a number"
		);
			
	result = cub_malloc_or_die(sizeof *result);
	*result = (t_cub_char_list){
		.value = first,
		.next = 0,
	};

	t_cub_char_list *tmp_ptr;

	char c2 = cub_read_char_or_die(fd);
	if (!cub_is_digit(c2)) {
		*last_out_ptr = c2;
		return cub_validate_color_number_or_die(result);
	}
	tmp_ptr = cub_malloc_or_die(sizeof *tmp_ptr);
	*tmp_ptr = (t_cub_char_list){ .value = c2, .next = result };
	result = tmp_ptr;

	char c3 = cub_read_char_or_die(fd);
	if (!cub_is_digit(c3)) {
		*last_out_ptr = c3;
		return cub_validate_color_number_or_die(result);
	}
	tmp_ptr = cub_malloc_or_die(sizeof *tmp_ptr);
	*tmp_ptr = (t_cub_char_list){ .value = c3, .next = result };
	result = tmp_ptr;

	char c4 = cub_read_char_or_die(fd);
	if (cub_is_digit(c4))
		cub_error_die(
			"cub_parse_color_number_or_die: "
			"number is too big"
		);

	*last_out_ptr = c4;

	int int_result = cub_validate_color_number_or_die(result);
	return int_result;
}

/*
spaces
red:
	number | number >= 0 && number < 256
spaces
comma
spaces
green:
	number | number >= 0 && number < 256
spaces
comma
spaces
blue:
	number | number >= 0 && number < 256
spaces
new line
*/
// Fix me: is order correct?
void cub_parse_color_or_die(
	int fd,
	t_cub_conf *conf_ptr,
	cub_parse_color_of_what_t what
) {
	char not_space = cub_skip_spaces_or_die(fd);
	char last;
	int red = cub_parse_color_number_or_die(not_space, fd, &last);
	cub_true_or_error_die(
		last == ',',
		"cub_parse_color_or_die: "
		"expected comma"
	);
	not_space = cub_skip_spaces_or_die(fd);
	int green = cub_parse_color_number_or_die(not_space, fd, &last);
	cub_true_or_error_die(
		last == ',',
		"cub_parse_color_or_die: "
		"expected comma"
	);
	not_space = cub_skip_spaces_or_die(fd);
	int blue = cub_parse_color_number_or_die(not_space, fd, &last);
	if (last == ' ')
	last = cub_skip_spaces_or_die(fd);
	cub_true_or_error_die(
		last == '\n' || last == '\r',
		"cub_parse_color_or_die: "
		"expected new line"
	);
	switch (what.value) {
	case cub_parse_color_of_ceiling:
		conf_ptr -> ceiling_red = red;
		conf_ptr -> ceiling_green = green;
		conf_ptr -> ceiling_blue = blue;
	break;
	case cub_parse_color_of_floor:
		conf_ptr -> floor_red = red;
		conf_ptr -> floor_green = green;
		conf_ptr -> floor_blue = blue;
	break;
	default:
		cub_write_loop_or_die(
			STDERR_FILENO,
			"cub_parse_color_or_die: unreachable"
		);
		exit(2);
	break;
	}
}

void cub_parse_ceiling_color_or_die(int fd, t_cub_conf *conf_ptr) {
	cub_parse_color_or_die(
		fd,
		conf_ptr,
		(cub_parse_color_of_what_t){cub_parse_color_of_ceiling}
	);
}

void cub_parse_floor_color_or_die(int fd, t_cub_conf *conf_ptr) {
	cub_parse_color_or_die(
		fd,
		conf_ptr,
		(cub_parse_color_of_what_t){cub_parse_color_of_floor}
	);
}

void cub_parse_entry_or_die(
	int fd,
	t_cub_conf *conf_ptr,
	_Bool first_entry,
	char not_new_line
) {
	char c1;
	if (first_entry)
		c1 = cub_read_char_or_die(fd);
	else
		c1 = not_new_line;
	switch (c1) {
	case 'F':
		cub_true_or_error_die(
			!(conf_ptr -> floor_set),
			"cub_parse_entry_or_die: "
			"floor is already set"
		);
		cub_parse_floor_color_or_die(fd, conf_ptr);
		conf_ptr -> floor_set = 1;
		return;
	break;
	case 'C':
		cub_true_or_error_die(
			!(conf_ptr -> ceiling_set),
			"cub_parse_entry_or_die: "
			"ceiling is already set"
		);
		cub_parse_ceiling_color_or_die(fd, conf_ptr);
		conf_ptr -> ceiling_set = 1;
		return;
	break;
	}
	char c2 = cub_read_char_or_die(fd);
	char not_space = cub_skip_spaces_or_die(fd);
	char *path = cub_parse_entry_value_or_die(
		not_space,
		fd
	);
	switch (c1) {
	case 'S':
		cub_true_or_error_die(
			c2 == 'O',
			"cub_parse_entry_or_die: "
			"no such config entry key"
		);
		if (conf_ptr -> path_south)
			cub_error_die(
				"cub_parse_entry_or_die: "
				"duplicate config entry key: south"
			);
		conf_ptr -> path_south = path;
		return;
	break;
	case 'N':
		cub_true_or_error_die(
			c2 == 'O',
			"cub_parse_entry_or_die: "
			"no such config entry key"
		);
		if (conf_ptr -> path_north)
			cub_error_die(
				"cub_parse_entry_or_die: "
				"duplicate config entry key: north"
			);
		conf_ptr -> path_north = path;
		return;
	break;
	case 'E':
		cub_true_or_error_die(
			c2 == 'A',
			"cub_parse_entry_or_die: "
			"no such config entry key"
		);
		if (conf_ptr -> path_east)
			cub_error_die(
				"cub_parse_entry_or_die: "
				"duplicate config entry key: east"
			);
		conf_ptr -> path_east = path;
		return;
	break;
	case 'W':
		cub_true_or_error_die(
			c2 == 'E',
			"cub_parse_entry_or_die: "
			"no such config entry key"
		);
		if (conf_ptr -> path_west)
			cub_error_die(
				"cub_parse_entry_or_die: "
				"duplicate config entry key: west"
			);
		conf_ptr -> path_west = path;
		return;
	break;
	}
}

char **cub_line_list_ptr_to_charss_or_die(
	t_cub_line_list *line_list_ptr,
	int *length_out
) {
	int len = 0;

	{
	t_cub_line_list *tmp_list_ptr = line_list_ptr;
	while (tmp_list_ptr) {
		len++;
		tmp_list_ptr = tmp_list_ptr -> next;
	} }

	char **charss = cub_malloc_or_die(sizeof(*charss) * (len + 1));
	charss[len] = 0;

	{
	t_cub_line_list *tmp_list_ptr = line_list_ptr;
	for (int i = 0; i < len; i++) {
		t_cub_line_list *next_list_ptr = tmp_list_ptr -> next;
		charss[i] =
			cub_char_list_to_chars_or_die(tmp_list_ptr->value);
		free(tmp_list_ptr);
		tmp_list_ptr = next_list_ptr;
	} }

	*length_out = len;
	return charss;
}

t_cub_conf cub_parse(char *path) {
	t_cub_conf conf = {0};

	cub_check_extension_or_die(path);
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		perror("Error\ncub_parse");
		exit(1);
	}

	char not_new_line;
	_Bool first = 1;
	for (int i = 0; i < 6; i++) {
		cub_parse_entry_or_die(fd, &conf, first, not_new_line);
		not_new_line = cub_skip_new_lines_or_die(fd);
		first = 0;
	}

	// Fix me: add _or_die
	t_cub_char_list *char_list_ptr =
		cub_fd_to_char_list_ptr_or_die(not_new_line, fd);

	// Fix me: add _or_die
	t_cub_line_list *line_list_ptr = cub_char_list_ptr_to_line_list_ptr(char_list_ptr);

	cub_replace_spaces_with_ones(line_list_ptr);

	cub_check_map_frame_or_die(line_list_ptr);

	conf.lines =
		cub_line_list_ptr_to_charss_or_die(
			line_list_ptr,
			&(conf.lines_length)
		);

	return conf;
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

void cub_error_die(char *message) {
	cub_write_loop_or_die(2, "Error\n");
	cub_write_loop_or_die(2, message);
	cub_write_loop_or_die(2, "\n");
	exit(1);
}

void cub_true_or_error_die(_Bool condition, char *message) {
	if (!condition) {
		cub_error_die(message);
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
			cub_write1loop_or_die(
				2,
				a_char_ptr->value
			);
		}
		cub_write1loop_or_die(2, '\n');
	}
}

void cub_check_map_top_or_bottom_or_die(t_cub_char_list *line) {
	while (1) {
		if (line == 0) break;
		cub_true_or_error_die(
			line->value == '1',
			"cub_check_map_top_or_bottom_or_die: "
			"map is not framed "
			"horizontally"
		);
		line = line -> next;
	}
}

void cub_check_map_empty_line_or_die(int length) {
	cub_true_or_error_die(
		length > 0,
		"cub_check_map_left_and_right_or_die: "
		"map line can't be empty because it must be in a frame"
	);
}

int cub_min(int a, int b) { return a < b ? a : b; }

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
			cub_true_or_error_die(
				curr_char_ptr -> value == '1',
				"cub_check_map_left_and_right_or_die: "
				"map’s right edge can't be zero"
			);
		if (first_column)
			cub_true_or_error_die(
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
		cub_true_or_error_die(
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
