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

int	cub_read1(int fd)
{
	int		result;
	char	c;
	int		much_read;

	much_read = read(fd, &c, 1);
	if (much_read == 1)
		result = c;
	else
		result = much_read;
	return (result);
}

int	cub_read1_or_die(int fd)
{
	int	much_read;

	much_read = cub_read1(fd);
	if (much_read == 0)
		return (-1);
	if (much_read == -1)
	{
		perror("Error\nread1_or_die");
		exit(1);
	}
	return (much_read);
}

char	cub_read_char_or_die(int fd)
{
	int	result;

	result = cub_read1_or_die(fd);
	if (result == -1)
	{
		cub_error_die(
			"cub_read1_char_or_die: "
			"expected a char, but got end of file");
	}
	return (result);
}
