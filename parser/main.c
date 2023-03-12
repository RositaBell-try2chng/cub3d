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

// Result of a parse
typedef struct {
	t_cub_line_list *lines;
} t_cub_conf;

// Fix me: not used
static int cub_write(int fd, char c) {
	while (1) {
		int much_written = write(fd, &c, 1);
		if (much_written == -1)
			return -1;
		if (much_written == 1)
			return 1;
	}
}

// Takes a file descriptor
// Returns -1 on failure, 0 on end of file, read character otherwise
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

// Takes a file descriptor
// Dies on error
// Returns -1 on end of file, read character otherwise
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
		case '\n':
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

		free(char_list_ptr);
		char_list_ptr = next_ptr;
	}
	return line_list_ptr;
}

// Input: path to .cub file
// Output: death or valid conf
t_cub_conf cub_parse(char *path) {
	t_cub_conf conf;

	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		perror("Error\ncub_parse");
		exit(1);
	}

	t_cub_char_list *char_list_ptr = cub_fd_to_char_list_ptr(fd);

	t_cub_line_list *line_list_ptr = cub_char_list_ptr_to_line_list_ptr(char_list_ptr);

	conf.lines = line_list_ptr;
	return conf;
}

int main(int argc, char **argv) {
	t_cub_conf conf = cub_parse(argv[1]);

	t_cub_line_list *line_list_ptr = conf.lines;

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
}
