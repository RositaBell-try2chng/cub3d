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
#include "mem.h"

void	*cub_malloc_or_die(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == 0)
	{
		perror("Error\ncub_malloc_or_die");
		exit(1);
	}
	return (result);
}

void	cub_memcpy(char *a, char *b, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		a[i] = b[i];
		i++;
	}
}
