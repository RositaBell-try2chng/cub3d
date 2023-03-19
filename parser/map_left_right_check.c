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

void	cub_check_map_empty_line_or_die(int length)
{
	cub_true_or_error_die(
		length > 0,
		"cub_check_map_left_and_right_or_die: "
		"map line can't be empty because it must be in a frame");
}

_Bool	cub_check_map_left_and_right_or_die_check(
	t_cub_char_list *curr_char_ptr,
	t_cub_char_list *prev_char_ptr,
	_Bool first_column
)
{
	if (curr_char_ptr == 0 || prev_char_ptr == 0)
		return (0);
	if (curr_char_ptr -> next == 0)
		cub_true_or_error_die(
			curr_char_ptr -> value == '1',
			"cub_check_map_left_and_right_or_die: "
			"map’s right edge can't be zero");
	if (first_column)
		cub_true_or_error_die(
			curr_char_ptr -> value == '1',
			"cub_check_map_left_and_right_or_die: "
			"map’s left edge can't be zero");
	return (1);
}

void	cub_check_map_left_and_right_or_die_advance(
	t_cub_check_map_left_and_right_or_die_args *args
)
{
	args->first_column = 0;
	args->curr_char_ptr = args->curr_char_ptr->next;
	args->prev_char_ptr = args->prev_char_ptr->next;
}

// Prev might be null
// First line is checked by a different function
// Everything in range [must_be_walls; ∞) must be '1'
// int must_be_walls = min(curr -> length, prev -> length);
// Perhaps: cliff is a weird word
void	cub_check_map_left_and_right_or_die(
	t_cub_line_list *prev,
	t_cub_line_list *curr
)
{
	t_cub_check_map_left_and_right_or_die_args	_;

	_.first_column = 1;
	cub_check_map_empty_line_or_die(curr->length);
	if (prev == 0)
		return ;
	_.curr_char_ptr = curr -> value;
	_.prev_char_ptr = prev -> value;
	while (1)
	{
		if (!cub_check_map_left_and_right_or_die_check(_.curr_char_ptr,
				_.prev_char_ptr, _.first_column))
			break ;
		cub_check_map_left_and_right_or_die_advance(&_);
	}
	if (_.curr_char_ptr == 0)
		_.curr_char_ptr = _.prev_char_ptr;
	while (_.curr_char_ptr)
	{
		cub_true_or_error_die(
			_.curr_char_ptr -> value == '1', "cub_check_map_left_and_right_or_"
			"die: map’s right cliff can't be zero");
		_.curr_char_ptr = _.curr_char_ptr -> next;
	}
}
