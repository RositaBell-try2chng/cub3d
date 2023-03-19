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

#include "cub_parser_private.h"

// Fix me: use new char function here
int	cub_parse_color_number_or_die(char first, int fd, char *last_out_ptr)
{
	t_cub_char_list	*result;
	char			c;
	t_cub_char_list	*tmp_ptr;

	if (!cub_is_digit(first))
		cub_error_die(
			"cub_parse_color_number_or_die: not parsing a number");
	result = new_char_list_or_die(0, first);
	c = cub_read_char_or_die(fd);
	if (!cub_is_digit(c))
		return (*last_out_ptr = c, cub_validate_color_number_or_die(result));
	tmp_ptr = new_char_list_or_die(result, c);
	result = tmp_ptr;
	c = cub_read_char_or_die(fd);
	if (!cub_is_digit(c))
		return (*last_out_ptr = c, cub_validate_color_number_or_die(result));
	tmp_ptr = new_char_list_or_die(result, c);
	result = tmp_ptr;
	c = cub_read_char_or_die(fd);
	if (cub_is_digit(c))
		cub_error_die("cub_parse_color_number_or_die: number is too big");
	*last_out_ptr = c;
	return (cub_validate_color_number_or_die(result));
}

void	red_green_blue_what(
	struct s_red_green_blue_what_args _
)
{
	if (_.what.value == cub_parse_color_of_ceiling)
	{
		_.conf_ptr->ceiling_red = _.red;
		_.conf_ptr->ceiling_green = _.green;
		_.conf_ptr->ceiling_blue = _.blue;
	}
	else if (_.what.value == cub_parse_color_of_floor)
	{
		_.conf_ptr->floor_red = _.red;
		_.conf_ptr->floor_green = _.green;
		_.conf_ptr->floor_blue = _.blue;
	}
	else
	{
		cub_write_loop_or_die(
			STDERR_FILENO,
			"cub_parse_color_or_die: unreachable");
		exit(2);
	}
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
// Fix me: outdated comment?
// Fix me: is order correct?
void	cub_parse_color_or_die(
	int fd,
	t_cub_conf *conf_ptr,
	t_cub_parse_color_of_what what
)
{
	char	not_space;
	char	last;
	int		r;
	int		g;
	int		b;

	r = cub_parse_color_number_or_die(cub_skip_spaces_or_die(fd), fd, &last);
	if (last == ' ')
		last = cub_skip_spaces_or_die(fd);
	cub_true_or_error_die(last == ',',
		"cub_parse_color_or_die: expected comma");
	g = cub_parse_color_number_or_die(cub_skip_spaces_or_die(fd), fd, &last);
	if (last == ' ')
		last = cub_skip_spaces_or_die(fd);
	cub_true_or_error_die(last == ',',
		"cub_parse_color_or_die: expected comma");
	b = cub_parse_color_number_or_die(cub_skip_spaces_or_die(fd), fd, &last);
	if (last == ' ')
		last = cub_skip_spaces_or_die(fd);
	cub_true_or_error_die(
		last == '\n' || last == '\r',
		"cub_parse_color_or_die: expected new line");
	red_green_blue_what((struct s_red_green_blue_what_args){
		conf_ptr, r, g, b, what,
	});
}
