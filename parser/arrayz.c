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

_Bool	cub_are_strings_equal(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

int	cub_strlen(char *input)
{
	int	result;

	result = 0;
	while (*input)
	{
		input++;
		result++;
	}
	return (result);
}

// Note: does not consume input
char	*cub_reverse_string_or_die(char *input)
{
	int		len;
	char	*output;
	int		i;

	len = cub_strlen(input);
	output = cub_malloc_or_die(len + 1);
	output[len] = 0;
	i = 0;
	while (i < len)
	{
		output[i] = input[len - i - 1];
		i++;
	}
	return (output);
}

char	*cub_char_list_to_chars_or_die(t_cub_char_list *list)
{
	int				len;
	char			*chars;
	t_cub_char_list	tmp;
	int				i;

	len = cub_char_list_len(list);
	chars = cub_malloc_or_die(len + 1);
	chars[len] = 0;
	i = 0;
	while (i < len)
	{
		if (list == 0)
			break ;
		chars[i] = list -> value;
		tmp = *list;
		free(list);
		list = &tmp;
		list = list -> next;
		i++;
	}
	return (chars);
}

char	**cub_line_list_ptr_to_charss_or_die(
	t_cub_line_list *line_list_ptr,
	int *length_out
)
{
	const int		len = line_list_length(line_list_ptr);
	int				i;
	char **const	charss = cub_malloc_or_die(sizeof(*charss) * (len + 1));
	t_cub_line_list	*next_list_ptr;

	charss[len] = 0;
	i = 0;
	while (i < len)
	{
		next_list_ptr = line_list_ptr -> next;
		charss[i] = cub_char_list_to_chars_or_die(line_list_ptr->value);
		free(line_list_ptr);
		line_list_ptr = next_list_ptr;
		i++;
	}
	*length_out = len;
	return (charss);
}
