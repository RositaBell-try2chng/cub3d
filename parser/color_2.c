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

int	cub_validate_color_number_len_1_or_die(t_cub_char_list *chars)
{
	int	result;

	result = cub_char_to_int(chars->value);
	free(chars);
	return (result);
}

int	cub_validate_color_number_len_2_or_die(t_cub_char_list *chars)
{
	int	second;
	int	first;
	int	result;

	second = cub_char_to_int(chars -> value);
	first = cub_char_to_int(chars -> next -> value);
	result = first * 10 + second;
	free(chars -> next);
	free(chars);
	return (result);
}

int	cub_validate_color_number_len_3_or_die(t_cub_char_list *chars)
{
	int	third;
	int	second;
	int	first;
	int	result;

	third = cub_char_to_int(chars -> value);
	second = cub_char_to_int(chars -> next -> value);
	first = cub_char_to_int(chars -> next -> next -> value);
	result = first * 10 * 10 + second * 10 + third;
	free(chars -> next -> next);
	free(chars -> next);
	free(chars);
	cub_true_or_error_die(
		result >= 0 && result < 256,
		"cub_validate_color_number_or_die: "
		"number is too big");
	return (result);
}

// One, two or three digits
int	cub_validate_color_number_or_die(t_cub_char_list *chars)
{
	if (chars -> next == 0)
		return (cub_validate_color_number_len_1_or_die(chars));
	else if (chars -> next -> next == 0)
		return (cub_validate_color_number_len_2_or_die(chars));
	else if (chars -> next -> next -> next == 0)
		return (cub_validate_color_number_len_3_or_die(chars));
	else
	{
		cub_write_loop_or_die(
			STDERR_FILENO,
			"cub_validate_color_number_or_die: unreachable");
		exit(2);
	}
}
