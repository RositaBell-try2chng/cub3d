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

void	cub_parse_ceiling_color_or_die(int fd, t_cub_conf *conf_ptr)
{
	cub_parse_color_or_die(
		fd,
		conf_ptr,
		(t_cub_parse_color_of_what){cub_parse_color_of_ceiling});
}

void	cub_parse_floor_color_or_die(int fd, t_cub_conf *conf_ptr)
{
	cub_parse_color_or_die(
		fd,
		conf_ptr,
		(t_cub_parse_color_of_what){cub_parse_color_of_floor});
}

void	cub_floor(int fd, t_cub_conf *conf_ptr)
{
	cub_true_or_error_die(!(conf_ptr -> floor_set),
		"cub_parse_entry_or_die: floor is already set");
	cub_parse_floor_color_or_die(fd, conf_ptr);
	conf_ptr -> floor_set = 1;
}

void	cub_ceiling(int fd, t_cub_conf *conf_ptr)
{
	cub_true_or_error_die(!(conf_ptr -> ceiling_set),
		"cub_parse_entry_or_die: ceiling is already set");
	cub_parse_ceiling_color_or_die(fd, conf_ptr);
	conf_ptr -> ceiling_set = 1;
}

void	cub_floor_or_ceiling(char c, int fd, t_cub_conf *conf_ptr)
{
	if (c == 'F')
		cub_floor(fd, conf_ptr);
	if (c == 'C')
		cub_ceiling(fd, conf_ptr);
}
