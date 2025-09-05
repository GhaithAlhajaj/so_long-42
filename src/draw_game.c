/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:36:20 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 20:16:54 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	render_tile(t_game *game, int x, int y, void *img)
{
	if (!game || !game->mlx || !game->win || !img)
		return ;
	mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y
		* TILE_SIZE);
}

static void	*get_texture(t_game *game, char tile)
{
	if (tile == '1')
		return (game->tex[0]);
	if (tile == 'C')
		return (game->tex[2]);
	if (tile == 'E')
		return (game->tex[3]);
	if (tile == 'P')
	{
		return (game->tex[5]);
	}
	return (game->tex[1]);
}

void	set_point(t_game *game, t_map *map, int x, int y)
{
	if (map->grid[y][x] == 'P')
	{
		game->map->player_x = x;
		game->map->player_y = y;
	}
	else if (map->grid[y][x] == 'E')
	{
		game->map->door_x = x;
		game->map->door_y = y;
	}
}

void	draw_world(t_game *game)
{
	t_map	*map;
	int		x;
	int		y;

	if (!game || !game->map || !game->tex[0] || !game->tex[1] || !game->tex[2]
		|| !game->tex[3] || !game->tex[4])
		return ;
	map = game->map;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			render_tile(game, x, y, get_texture(game, map->grid[y][x]));
			set_point(game, map, x, y);
			x++;
		}
		y++;
	}
}
