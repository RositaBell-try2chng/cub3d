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

void	perror_die(char *m)
{
	perror(m);
	exit(1);
}

void	cub_error_die(char *message)
{
	cub_write_loop_or_die(2, "Error\n");
	cub_write_loop_or_die(2, message);
	cub_write_loop_or_die(2, "\n");
	exit(1);
}

void	cub_true_or_error_die(_Bool condition, char *message)
{
	if (!condition)
		cub_error_die(message);
}
