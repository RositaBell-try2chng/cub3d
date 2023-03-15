#include <stddef.h>

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

void cub_write1loop_or_die(int fd, char c);

void cub_write_loop_or_die(int fd, char *s);

_Bool cub_are_strings_equal(char *s1, char *s2);

static void cub_check_extension_or_die(char *name);

// Takes a file descriptor
// Returns -1 on failure, 0 on end of file, read character otherwise
int cub_read1(int fd);

// Takes a file descriptor
// Dies on error
// Returns -1 on end of file, read character otherwise
int read1_or_die(int fd);

void *cub_malloc_or_die(size_t size);

t_cub_char_list *cub_fd_to_char_list_ptr(int fd);

t_cub_line_list *
cub_char_list_ptr_to_line_list_ptr(t_cub_char_list *char_list_ptr);

// Input: path to .cub file
// Output: death or valid conf
t_cub_conf cub_parse(char *path);

int cub_check_extension_or_die_test(char *path);

void cub_replace_spaces_with_ones(t_cub_line_list *lines);

void cub_check_map_frame_or_die(t_cub_line_list *lines);
