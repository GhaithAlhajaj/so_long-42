/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:36:20 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 12:37:37 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	update_frame(t_game *game)
{
	draw_world(game);
	if (game->map->collectibles == 0
		&& game->map->grid[game->map->player_y][game->map->player_x] == 'E')
	{
		ft_putstr_fd("You won!\n", 1);
		close_game(game);
	}
	return (0);
}
