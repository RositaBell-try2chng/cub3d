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

#include "../cub.h"

#include "cub_parser.h"
#include "cub_parser_private.h"

// Fix me: use this everywhere
// _Bool is_line_break(char c) { return c == '\n' || c == '\r'; }

#define EXTENSION ".cub"
// Note: does not consume input
void	cub_check_extension_or_die(char *name)
{
	char	*reversed;
	char	*extension_reversed;
	int		i;

	cub_true_or_error_die(
		cub_strlen(name) >= (int)(sizeof EXTENSION) - 1,
		"cub_check_extension_or_die: wrong extension");
	reversed
		= cub_reverse_string_or_die(name);
	extension_reversed
		= cub_reverse_string_or_die(EXTENSION);
	i = 0;
	while (i < (int)(sizeof EXTENSION) - 1)
	{
		cub_true_or_error_die(
			extension_reversed[i] == reversed[i],
			"cub_check_extension_or_die: wrong extension");
		i++;
	}
	free(extension_reversed);
	free(reversed);
}
#undef EXTENSION

// Fix me: sss should be ss?
// Fix me: this is madness
// const char		*ss[] = {"south", "north", "east", "west", 0};
void	c22(
	int i1,
	char c2,
	char *path,
	t_cub_conf *conf_ptr
)
{
	const char		*s2 = "OOAE";
	char **const	sss[] = {&(conf_ptr->path_south),
		&(conf_ptr->path_north), &(conf_ptr->path_east),
		&(conf_ptr->path_west), 0};

	cub_true_or_error_die(c2 == s2[i1], "c22: no such key");
	if (*(sss[i1]))
		cub_error_die("c22: duplicate key");
	*(sss[i1]) = path;
}

// Fix me: this is madness
void	c2(char c1, char c2, int fd, t_cub_conf *conf_ptr)
{
	const char	not_space = cub_skip_spaces_or_die(fd);
	const char	*path = cub_parse_entry_value_or_die(not_space, fd);
	int			i;

	if (!(c1 == 'S' || c1 == 'N' || c1 == 'E' || c1 == 'W'))
	{
		cub_write_loop_or_die(
			STDERR_FILENO,
			"c22: no such key");
		exit(1);
	}
	i = 0;
	while (c1 != "SNEW"[i])
		i++;
	c22(i, c2, (char *)path, conf_ptr);
}

// Fix me: this is madness
void	cub_parse_entry_or_die(
	int fd,
	t_cub_conf *conf_ptr,
	_Bool first_entry,
	char not_new_line
)
{
	char	c1;

	if (first_entry)
		c1 = cub_read_char_or_die(fd);
	else
		c1 = not_new_line;
	if (c1 == 'F' || c1 == 'C')
	{
		cub_floor_or_ceiling(c1, fd, conf_ptr);
		return ;
	}
	c2(c1, cub_read_char_or_die(fd), fd, conf_ptr);
}

t_cub_conf	cub_parse(char *path)
{
	struct s_cub_parse_args	_;

	_ = (struct s_cub_parse_args){{0}, 0, 0, 0, 0, 0, 0};
	cub_check_extension_or_die(path);
	_.fd = open(path, O_RDONLY);
	if (_.fd == -1)
		perror_die("Error\ncub_parse");
	_.first = 1;
	while (_.i < 6)
	{
		cub_parse_entry_or_die(_.fd, &(_.conf), _.first, _.not_new_line);
		_.not_new_line = cub_skip_new_lines_or_die(_.fd);
		_.first = 0;
		_.i++;
	}
	_.char_list_ptr = cub_fd_to_char_list_ptr_or_die(_.not_new_line, _.fd);
	_.line_list_ptr = cub_char_list_ptr_to_line_list_ptr(_.char_list_ptr);
	cub_replace_spaces_with_ones(_.line_list_ptr);
	cub_check_map_frame_or_die(_.line_list_ptr);
	_.conf.lines = cub_line_list_ptr_to_charss_or_die(
			_.line_list_ptr,
			&(_.conf.lines_length));
	return (_.conf);
}
