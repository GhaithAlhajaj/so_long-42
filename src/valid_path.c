/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:36:20 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 22:02:49 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	lock_door_for_dfs(char **grid, int width, int height)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (grid[y][x] == 'E')
			{
				grid[y][x] = '1';
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	dfs(int x, int y, t_dfs_data *data)
{
	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return ;
	if (data->grid[y][x] == '1' || data->grid[y][x] == 'X')
		return ;
	if (data->grid[y][x] == 'C')
		(*data->collect)--;
	else if (data->grid[y][x] == 'E')
		(*data->exit)--;
	data->grid[y][x] = 'X';
	dfs(x + 1, y, data);
	dfs(x - 1, y, data);
	dfs(x, y + 1, data);
	dfs(x, y - 1, data);
}

void	free_grid(char **grid, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static char	**copy_grid(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->grid[i]);
		if (!copy[i])
		{
			free_grid(copy, i);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	valid_path(t_map *map)
{
	char		**temp_map;
	t_dfs_data	data;
	int			temp_collect;
	int			temp_exit;

	temp_collect = map->collectibles;
	temp_exit = map->exit_flag;
	temp_map = copy_grid(map);
	if (!temp_map)
		return (0);
	data.grid = temp_map;
	data.width = map->width;
	data.height = map->height;
	data.collect = &temp_collect;
	data.exit = &temp_exit;
	dfs(map->player_x, map->player_y, &data);
	free_grid(temp_map, map->height);
	return (temp_collect == 0 && temp_exit == 0);
}
