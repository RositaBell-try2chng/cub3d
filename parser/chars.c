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

t_cub_char_list	*cub_fd_to_char_list_ptr_or_die_helper(
	t_cub_char_list *char_list_ptr,
	int fd
)
{
	char			prev;
	int				c;
	t_cub_char_list	*tmp_ptr;

	prev = 0;
	while (1)
	{
		c = cub_read1_or_die(fd);
		if (c == -1)
		{
			if (prev != '\n' && prev != '\r')
				cub_error_die(
					"cub_fd_to_char_list_ptr_or_die: "
					"configuration file must end in a line break");
			break ;
		}
		tmp_ptr = cub_malloc_or_die(sizeof(*tmp_ptr));
		*tmp_ptr = (t_cub_char_list){
			.value = c,
			.next = char_list_ptr,
		};
		char_list_ptr = tmp_ptr;
		prev = c;
	}
	return (char_list_ptr);
}

// Fix me: name is incorrect:
// function also verifies that configuration file ends in a line break
// Close fd since resource is consumed
t_cub_char_list	*cub_fd_to_char_list_ptr_or_die(char first, int fd)
{
	t_cub_char_list	*char_list_ptr;

	char_list_ptr = cub_malloc_or_die(sizeof(*char_list_ptr));
	*char_list_ptr = (t_cub_char_list)
	{
		.value = first,
		.next = 0,
	};
	char_list_ptr = cub_fd_to_char_list_ptr_or_die_helper(
			char_list_ptr,
			fd);
	close(fd);
	return (char_list_ptr);
}

t_cub_char_list	*new_char_list_or_die(t_cub_char_list *next, char value)
{
	t_cub_char_list	*result;

	result = cub_malloc_or_die(sizeof(*result));
	*result = (t_cub_char_list){
		.next = next,
		.value = value,
	};
	return (result);
}

t_cub_char_list	*cub_reverse_char_list_or_die(t_cub_char_list *input)
{
	t_cub_char_list	*output;
	t_cub_char_list	tmp_input;
	t_cub_char_list	*tmp_output_ptr;

	output = 0;
	while (input)
	{
		tmp_output_ptr = cub_malloc_or_die(sizeof(*tmp_output_ptr));
		*tmp_output_ptr = (t_cub_char_list){
			.value = input -> value,
			.next = output,
		};
		output = tmp_output_ptr;
		tmp_input = *input;
		free(input);
		input = tmp_input . next;
	}
	return (output);
}

int	cub_char_list_len(t_cub_char_list *list)
{
	int	result;

	result = 0;
	while (list)
	{
		result++;
		list = list -> next;
	}
	return (result);
}
