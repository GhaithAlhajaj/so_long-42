/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:36:20 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 21:00:10 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	free_map(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->grid)
		{
			i = 0;
			while (i < map->height)
				free(map->grid[i++]);
			free(map->grid);
		}
		free(map);
	}
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		if (game->tex[i])
			mlx_destroy_image(game->mlx, game->tex[i]);
		i++;
	}
}

void	free_game(t_game *game)
{
	free_map(game->map);
	free_textures(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

int	chk_format(int argc, char *map_name)
{
	if (argc != 2)
	{
		write(2, "Wrong Format!\ncorrect Format: So_long Map\n", 43);
		exit(1);
	}
	if (ft_strrchr(map_name, '.'))
	{
		if (ft_strcmp(ft_strrchr(map_name, '.'), ".ber") == 0)
			return (1);
		else
		{
			write(2, "Wrong Extension\n", 17);
			exit(1);
		}
	}
	else
	{
		ft_putstr_fd("No Extension Found\n", 2);
		exit(1);
	}
}
