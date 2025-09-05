/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:36:20 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 13:36:30 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	check_border(t_map *map)
{
	int	i;
	int	w;
	int	h;

	w = map->width;
	h = map->height;
	if (!map->grid)
		return (0);
	i = 0;
	while (i < w)
	{
		if (map->grid[0][i] != '1' || map->grid[h - 1][i] != '1')
			return (0);
		i++;
	}
	i = 1;
	while (i < h - 1)
	{
		if (map->grid[i][0] != '1' || map->grid[i][w - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	valid_shape(t_map *map)
{
	int	i;

	if (!map->grid || map->height == 0)
	{
		ft_printf("❌ Map grid is NULL or height is 0\n");
		return (0);
	}
	map->width = (int)ft_strlen(map->grid[0]);
	i = 1;
	while (i < map->height)
	{
		if ((int)ft_strlen(map->grid[i]) != map->width)
		{
			ft_printf("❌ Row %d has an invalid width\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}
