/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:36:20 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 22:05:03 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	load_texture(t_game *game, int index, char *path)
{
	game->tex[index] = mlx_xpm_file_to_image(game->mlx, path, &game->tex_width,
			&game->tex_height);
	if (!game->tex[index])
	{
		ft_printf("Error: Could not load '%s'\n", path);
		close_game(game);
	}
}

static void	load_assets(t_game *game)
{
	int			i;
	const char	*paths[10] = {"img/xpm/wall.xpm", "img/xpm/floor.xpm",
		"img/xpm/collect.xpm", "img/xpm/doorC.xpm", "img/xpm/doorO.xpm",
		"img/xpm/charac.xpm", "img/xpm/character_left.xpm",
		"img/xpm/character_right.xpm", "img/xpm/charact_up.xpm",
		"img/xpm/charact_down.xpm"};

	i = 0;
	while (i < 10)
	{
		load_texture(game, i, (char *)paths[i]);
		if (!game->tex[i])
		{
			ft_printf("Error: Failed to load asset at index %d: %s\n", i,
				paths[i]);
			close_game(game);
		}
		i++;
	}
}

static void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->map = safe_alloc(sizeof(t_map));
	game->map->moves = 0;
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error: mlx init failed\n", 2);
		free_game(game);
		return (1);
	}
	game->win = mlx_new_window(game->mlx, game->map->width * 60,
			game->map->height * 60, "Maze");
	if (!game->win)
	{
		ft_putstr_fd("Error: window creation failed\n", 2);
		free_game(game);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	chk_format(argc, argv[1]);
	init_game(&game);
	read_map(game.map, argv[1]);
	if (!valid_shape(game.map) || !check_layout(game.map)
		|| !valid_path(game.map))
	{
		ft_putstr_fd("Map error: unreachable element\n", 2);
		free_game(&game);
		return (1);
	}
	if (init_mlx(&game))
		return (1);
	load_assets(&game);
	draw_world(&game);
	game.map->last_tile = '0';
	mlx_key_hook(game.win, manage_key, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
