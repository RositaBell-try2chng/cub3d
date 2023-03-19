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

t_cub_char_list	*cub_parse_until_got_new_line_or_die(
	int fd,
	t_cub_char_list *previous
)
{
	t_cub_char_list	*result;
	char			c;
	t_cub_char_list	*tmp_ptr;

	result = previous;
	while (1)
	{
		c = cub_read_char_or_die(fd);
		if (c == '\n' || c == '\r')
			return (result);
		else
		{
			tmp_ptr = cub_malloc_or_die(sizeof(*tmp_ptr));
			*tmp_ptr = (t_cub_char_list){
				.value = c,
				.next = result,
			};
			result = tmp_ptr;
		}
	}
}

char	*cub_parse_entry_value_or_die(char first, int fd)
{
	t_cub_char_list	*first_char_list_ptr;

	if (first == '\n' || first == '\r')
		cub_error_die(
			"cub_parse_entry_value_or_die: "
			"entry value can't be empty");
	first_char_list_ptr = cub_malloc_or_die(sizeof(*first_char_list_ptr));
	*first_char_list_ptr = (t_cub_char_list)
	{
		.value = first,
		.next = 0,
	};
	return (
		cub_char_list_to_chars_or_die(
			cub_reverse_char_list_or_die(
				cub_parse_until_got_new_line_or_die(
					fd,
					first_char_list_ptr))));
}
