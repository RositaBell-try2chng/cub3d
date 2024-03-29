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

#ifndef CUB_PARSER_H
# define CUB_PARSER_H

# include <stddef.h>

// Result of a parse
// Malloc'ed lines, paths
typedef struct s_cub_conf {
	char	**lines;
	int		lines_length;
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
	_Bool	floor_set;
	int		floor_red;
	int		floor_green;
	int		floor_blue;
	_Bool	ceiling_set;
	int		ceiling_red;
	int		ceiling_green;
	int		ceiling_blue;
}	t_cub_conf;

// Input: path to .cub file
// Output: death or valid conf
t_cub_conf	cub_parse(char *path);

#endif
