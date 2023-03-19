/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghelman <alan.urman@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:46:42 by ghelman           #+#    #+#             */
/*   Updated: 2023/03/19 12:46:42 by ghelman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_PARSER_PRIVATE_H
# define CUB_PARSER_PRIVATE_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# include "cub_parser.h"

typedef struct s_cub_char_list {
	char					value;
	struct s_cub_char_list	*next;
}	t_cub_char_list;

enum e_cub_parse_color_of_what_e {
	cub_parse_color_of_ceiling,
	cub_parse_color_of_floor,
};

typedef struct s_cub_parse_color_of_what_s {
	enum e_cub_parse_color_of_what_e	value;
}	t_cub_parse_color_of_what;

typedef struct s_cub_line_list {
	int						length;
	t_cub_char_list			*value;
	struct s_cub_line_list	*next;
}	t_cub_line_list;

void			cub_parse_entry_or_die(
					int fd,
					t_cub_conf *conf,
					_Bool first_entry,
					char not_new_line);

void			cub_write1loop_or_die(int fd, char c);
void			cub_write_loop_or_die(int fd, char *s);

_Bool			cub_are_strings_equal(char *s1, char *s2);
int				cub_strlen(char *input);
char			*cub_reverse_string_or_die(char *input);

void			cub_check_extension_or_die(char *name);

int				cub_read1(int fd);
int				cub_read1_or_die(int fd);
char			cub_read_char_or_die(int fd);

void			*cub_malloc_or_die(size_t size);

t_cub_char_list	*cub_fd_to_char_list_ptr_or_die_helper(
					t_cub_char_list *char_list_ptr,
					int fd);

t_cub_char_list	*cub_fd_to_char_list_ptr_or_die(char first, int fd);

char			cub_skip_spaces_or_die(int fd);
char			cub_skip_new_lines_or_die(int fd);

struct s_cub_char_list_ptr_to_line_list_ptr_helper_args
{
	t_cub_char_list	*char_list_ptr;
	t_cub_line_list	*line_list_ptr;
	t_cub_char_list	*next_ptr;
	char			c;
	t_cub_line_list	*tmp_line_ptr;
	t_cub_char_list	*tmp_ptr_2;
};

t_cub_line_list	*new_line_list_or_die(t_cub_line_list *next);
t_cub_line_list	*cub_char_list_ptr_to_line_list_ptr_helper(
					struct s_cub_char_list_ptr_to_line_list_ptr_helper_args _);

t_cub_line_list	*cub_char_list_ptr_to_line_list_ptr(
					t_cub_char_list *char_list_ptr);

t_cub_char_list	*new_char_list_or_die(t_cub_char_list *next, char value);

t_cub_char_list	*cub_parse_until_got_new_line_or_die(
					int fd,
					t_cub_char_list *previous);

t_cub_char_list	*cub_reverse_char_list_or_die(t_cub_char_list *input);
int				cub_char_list_len(t_cub_char_list *list);
char			*cub_char_list_to_chars_or_die(t_cub_char_list *list);
char			*cub_parse_entry_value_or_die(char first, int fd);
void			cub_write_char_list_or_die(int fd, t_cub_char_list *ptr);
_Bool			cub_is_digit(char c);
int				cub_char_to_int(char c);

int				cub_validate_color_number_len_1_or_die(t_cub_char_list *chars);
int				cub_validate_color_number_len_2_or_die(t_cub_char_list *chars);
int				cub_validate_color_number_len_3_or_die(t_cub_char_list *chars);
int				cub_validate_color_number_or_die(t_cub_char_list *chars);
int				cub_parse_color_number_or_die(
					char first,
					int fd,
					char *last_out_ptr);

struct s_red_green_blue_what_args {
	t_cub_conf					*conf_ptr;
	int							red;
	int							green;
	int							blue;
	t_cub_parse_color_of_what	what;
};

void			red_green_blue_what(
					struct s_red_green_blue_what_args _);

void			cub_parse_color_or_die(
					int fd,
					t_cub_conf *conf_ptr,
					t_cub_parse_color_of_what what);

void			cub_parse_ceiling_color_or_die(int fd, t_cub_conf *conf_ptr);
void			cub_parse_floor_color_or_die(int fd, t_cub_conf *conf_ptr);
void			cub_floor(int fd, t_cub_conf *conf_ptr);
void			cub_ceiling(int fd, t_cub_conf *conf_ptr);
void			cub_floor_or_ceiling(char c, int fd, t_cub_conf *conf_ptr);

void			c22(
					int i1,
					char c2,
					char *path,
					t_cub_conf *conf_ptr);

void			c2(char c1, char c2, int fd, t_cub_conf *conf_ptr);

void			cub_parse_entry_or_die(
					int fd,
					t_cub_conf *conf_ptr,
					_Bool first_entry,
					char not_new_line);

int				line_list_length(t_cub_line_list *l);

char			**cub_line_list_ptr_to_charss_or_die(
					t_cub_line_list *line_list_ptr,
					int *length_out);

struct s_cub_parse_args {
	t_cub_conf		conf;
	char			not_new_line;
	_Bool			first;
	int				fd;
	int				i;
	t_cub_char_list	*char_list_ptr;
	t_cub_line_list	*line_list_ptr;
};

t_cub_conf		cub_parse(char *path);
void			cub_replace_spaces_with_ones(t_cub_line_list *lines);

void			perror_die(char *m);
void			cub_error_die(char *message);
void			cub_true_or_error_die(_Bool condition, char *message);

void			cub_check_map_top_or_bottom_or_die(t_cub_char_list *line);
void			cub_check_map_empty_line_or_die(int length);

_Bool			cub_check_map_left_and_right_or_die_check(
					t_cub_char_list *curr_char_ptr,
					t_cub_char_list *prev_char_ptr,
					_Bool first_column);

typedef struct s_cub_check_map_left_and_right_or_die_args {
	_Bool			first_column;
	t_cub_char_list	*curr_char_ptr;
	t_cub_char_list	*prev_char_ptr;
}	t_cub_check_map_left_and_right_or_die_args;

void			cub_check_map_left_and_right_or_die_advance(
					t_cub_check_map_left_and_right_or_die_args *args);

void			cub_check_map_left_and_right_or_die(
					t_cub_line_list *prev,
					t_cub_line_list *curr);

void			cub_check_map_frame_or_die(t_cub_line_list *lines);

#endif
