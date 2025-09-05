/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:36:20 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 18:12:39 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	manage_key(int key, t_game *game)
{
	if (key == XK_Escape)
		close_game(game);
	else if (key == XK_w)
		execute_move(game, 0, -1, 'U');
	else if (key == XK_s)
		execute_move(game, 0, 1, 'D');
	else if (key == XK_a)
		execute_move(game, -1, 0, 'L');
	else if (key == XK_d)
		execute_move(game, 1, 0, 'R');
	else
		return (0);
	return (0);
}
