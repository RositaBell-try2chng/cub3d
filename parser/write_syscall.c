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

void	cub_write1loop_or_die(int fd, char c)
{
	int	much_written;

	while (1)
	{
		much_written = write(fd, &c, 1);
		if (much_written == 1)
			return ;
		if (much_written == -1)
		{
			perror("Error\ncub_write1loop_or_die");
			exit(1);
		}
	}
}

void	cub_write_loop_or_die(int fd, char *s)
{
	char	c;

	c = *s;
	while (c != 0)
	{
		cub_write1loop_or_die(fd, c);
		c = *++s;
	}
}
