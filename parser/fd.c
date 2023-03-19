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

char	cub_skip_spaces_or_die(int fd)
{
	char	result;

	result = ' ';
	while (result == ' ')
	{
		result = cub_read_char_or_die(fd);
	}
	return (result);
}

char	cub_skip_new_lines_or_die(int fd)
{
	char	result;

	result = '\n';
	while (result == '\n' || result == '\r')
	{
		result = cub_read_char_or_die(fd);
	}
	return (result);
}

void	cub_write_char_list_or_die(int fd, t_cub_char_list *ptr)
{
	while (ptr)
	{
		cub_write1loop_or_die(fd, ptr -> value);
		ptr = ptr -> next;
	}
}
