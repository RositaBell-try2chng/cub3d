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

#ifndef CUB_LINUX_H
# define CUB_LINUX_H

// # include <X11/X.h> // Seems to be working without this
# include <X11/keysym.h>

enum e_cub_key_bindings {
	ESC = XK_Escape,
	W = XK_w,
	A = XK_a,
	S = XK_s,
	D = XK_d,
	RIGHT_ARROW = XK_Right,
	LEFT_ARROW = XK_Left,
};

#endif
