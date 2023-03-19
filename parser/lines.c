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

t_cub_line_list	*cub_char_list_ptr_to_line_list_ptr_helper(
	struct s_cub_char_list_ptr_to_line_list_ptr_helper_args _
)
{
	while (1)
	{
		if (_.char_list_ptr == 0)
			break ;
		_.next_ptr = _.char_list_ptr->next;
		_.c = _.char_list_ptr->value;
		if (_.c == '\n' || _.c == '\r')
		{
			_.tmp_line_ptr = new_line_list_or_die(_.line_list_ptr);
			_.line_list_ptr = _.tmp_line_ptr;
		}
		else
		{
			_.tmp_ptr_2 = new_char_list_or_die(_.line_list_ptr->value, _.c);
			_.line_list_ptr->value = _.tmp_ptr_2;
			_.line_list_ptr->length++;
		}
		free(_.char_list_ptr);
		_.char_list_ptr = _.next_ptr;
	}
	return (_.line_list_ptr);
}

// Fix me: outdated comment?
// Else: prepend char to curr char_list
// Fix me: add _or_die
t_cub_line_list
	*cub_char_list_ptr_to_line_list_ptr(t_cub_char_list *char_list_ptr)
{
	struct s_cub_char_list_ptr_to_line_list_ptr_helper_args	_;

	_ = (struct s_cub_char_list_ptr_to_line_list_ptr_helper_args){0};
	_.line_list_ptr = 0;
	_.line_list_ptr
		= cub_char_list_ptr_to_line_list_ptr_helper(
			(struct s_cub_char_list_ptr_to_line_list_ptr_helper_args){
			char_list_ptr,
			_.line_list_ptr,
			_.next_ptr,
			_.c,
			_.tmp_line_ptr,
			_.tmp_ptr_2});
	return (_.line_list_ptr);
}

t_cub_line_list	*new_line_list_or_die(t_cub_line_list *next)
{
	t_cub_line_list	*result;

	result = cub_malloc_or_die(sizeof(*result));
	*result = (t_cub_line_list){
		.next = next,
		.value = 0,
		.length = 0,
	};
	return (result);
}

int	line_list_length(t_cub_line_list *l)
{
	int	result;

	result = 0;
	while (l)
	{
		l = l -> next;
		result++;
	}
	return (result);
}
