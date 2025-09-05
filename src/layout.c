/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:33:42 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 18:06:19 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	is_valid_char(char ch, int x, int y)
{
	if (ch != '0' && ch != '1' && ch != 'P' && ch != 'E' && ch != 'C')
	{
		ft_printf("❌ Invalid char '%c' at [%d][%d]\n", ch, y, x);
		return (0);
	}
	return (1);
}

static void	count_tile(char ch, int *p, int *e, int *c)
{
	if (ch == 'P')
		(*p)++;
	else if (ch == 'E')
		(*e)++;
	else if (ch == 'C')
		(*c)++;
}

static int	scan_map(t_map *map, int *p, int *e, int *c)
{
	int		x;
	int		y;
	char	ch;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			ch = map->grid[y][x];
			if (!is_valid_char(ch, x, y))
				return (0);
			if (ch == 'P')
			{
				map->player_x = x;
				map->player_y = y;
			}
			count_tile(ch, p, e, c);
		}
	}
	return (1);
}

static int	validate_counts(int p, int e, int c, t_map *map)
{
	map->collectibles = c;
	map->exit_flag = e;
	if (p != 1)
		ft_printf("❌ Player count: %d (should be 1)\n", p);
	if (e != 1)
		ft_printf("❌ Exit count: %d (should be 1)\n", e);
	if (c == 0)
		ft_printf("❌ No collectibles found\n");
	if (!check_border(map))
		ft_printf("❌ Border check failed\n");
	return (p == 1 && e == 1 && c > 0 && check_border(map));
}

int	check_layout(t_map *map)
{
	int	p;
	int	e;
	int	c;

	p = 0;
	e = 0;
	c = 0;
	if (!map->grid)
	{
		ft_printf("❌ Map grid is NULL\n");
		return (0);
	}
	if (!scan_map(map, &p, &e, &c))
		return (0);
	return (validate_counts(p, e, c, map));
}
