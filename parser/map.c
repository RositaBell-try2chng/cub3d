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

void	cub_replace_spaces_with_ones(t_cub_line_list *lines)
{
	t_cub_line_list	*a_line_ptr;
	t_cub_char_list	*a_char_ptr;

	a_line_ptr = lines;
	while (a_line_ptr != 0)
	{
		a_char_ptr = a_line_ptr->value;
		while (a_char_ptr != 0)
		{
			if (a_char_ptr->value == ' ')
				a_char_ptr->value = '1';
			a_char_ptr = a_char_ptr->next;
		}
		a_line_ptr = a_line_ptr->next;
	}
}

void	cub_check_map_top_or_bottom_or_die(t_cub_char_list *line)
{
	while (1)
	{
		if (line == 0)
			break ;
		cub_true_or_error_die(
			line->value == '1',
			"cub_check_map_top_or_bottom_or_die: "
			"map is not framed "
			"horizontally");
		line = line->next;
	}
}

void	cub_check_map_frame_or_die(t_cub_line_list *lines)
{
	_Bool			first_row;
	_Bool			last_row;
	t_cub_line_list	*prev;
	t_cub_line_list	*a_line_ptr;

	prev = 0;
	first_row = 1;
	a_line_ptr = lines;
	while (a_line_ptr != 0)
	{
		last_row = a_line_ptr->next == 0;
		if (first_row || last_row)
			cub_check_map_top_or_bottom_or_die(a_line_ptr->value);
		cub_check_map_left_and_right_or_die(prev, a_line_ptr);
		first_row = 0;
		prev = a_line_ptr;
		a_line_ptr = a_line_ptr->next;
	}
}
