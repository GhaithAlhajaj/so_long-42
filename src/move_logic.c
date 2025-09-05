/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:36:20 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 21:34:14 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	replace_player(t_game *game, char move)
{
	if (move == 'R')
		mlx_put_image_to_window(game->mlx, game->win, game->tex[7],
			game->map->player_x * TILE_SIZE, game->map->player_y * TILE_SIZE);
	else if (move == 'L')
		mlx_put_image_to_window(game->mlx, game->win, game->tex[6],
			game->map->player_x * TILE_SIZE, game->map->player_y * TILE_SIZE);
	else if (move == 'U')
		mlx_put_image_to_window(game->mlx, game->win, game->tex[8],
			game->map->player_x * TILE_SIZE, game->map->player_y * TILE_SIZE);
	else if (move == 'D')
		mlx_put_image_to_window(game->mlx, game->win, game->tex[9],
			game->map->player_x * TILE_SIZE, game->map->player_y * TILE_SIZE);
}

void	handle_door(t_game *game)
{
	if (game->map->collectibles == 0)
	{
		game->map->exit_flag = 1;
		mlx_put_image_to_window(game->mlx, game->win, game->tex[4],
			game->map->door_x * TILE_SIZE, game->map->door_y * TILE_SIZE);
	}
	else
		mlx_put_image_to_window(game->mlx, game->win, game->tex[3],
			game->map->door_x * TILE_SIZE, game->map->door_y * TILE_SIZE);
}

void	execute_move(t_game *game, int dx, int dy, char move)
{
	int		x;
	int		y;
	char	next;

	x = game->map->player_x + dx;
	y = game->map->player_y + dy;
	if (x < 0 || y < 0 || x >= game->map->width || y >= game->map->height)
		return ;
	next = game->map->grid[y][x];
	if (next == '1')
		return ;
	if (next == 'C')
		game->map->collectibles--;
	if (next == 'E' && game->map->collectibles == 0)
		close_game(game);
	update_player_position(game, dx, dy, move);
}

void	update_player_position(t_game *game, int dx, int dy, char move)
{
	int		x;
	int		y;
	char	next;

	x = game->map->player_x + dx;
	y = game->map->player_y + dy;
	next = game->map->grid[y][x];
	if (game->map->last_tile == 'E')
		game->map->grid[game->map->player_y][game->map->player_x] = 'E';
	else
		game->map->grid[game->map->player_y][game->map->player_x] = '0';
	game->map->grid[y][x] = 'P';
	game->map->player_x = x;
	game->map->player_y = y;
	game->map->moves++;
	ft_printf("Moves: %d\n", game->map->moves);
	handle_door(game);
	replace_player(game, move);
	if (game->map->last_tile != 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->tex[1], (x - dx) * TILE_SIZE, (y - dy) * TILE_SIZE);
	game->map->last_tile = next;
}
