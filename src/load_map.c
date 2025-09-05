/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:36:20 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 22:02:10 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	get_line_count(const char *file, t_map *map)
{
	int		fd;
	int		count;
	char	*line;

	fd = open_level(file, map);
	count = 0;
	if (fd == -1)
	{
		ft_printf("Error: Failed to open file %s\n", file);
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static void	handle_line_error(int i, int fd, const char *file, t_map *map)
{
	int	j;

	j = 0;
	while (j < i)
		free(map->grid[j++]);
	free(map->grid);
	ft_printf("Error: Failed to read line %d from file %s\n", i + 1, file);
	close(fd);
	free(map);
	exit(1);
}

static void	read_lines(t_map *map, int fd, const char *file)
{
	char	*line;
	size_t	len;
	int		i;

	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			handle_line_error(i, fd, file, map);
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		map->grid[i++] = line;
	}
	map->grid[i] = NULL;
}

static void	alloc_grid(t_map *map, int fd)
{
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
	{
		ft_printf("Error: Memory allocation failed for map->grid\n");
		close(fd);
		free(map);
		exit(1);
	}
}

void	read_map(t_map *map, const char *file)
{
	int	fd;

	fd = open_level(file, map);
	if (fd == -1)
	{
		ft_printf("Error: Failed to open file %s\n", file);
		return ;
	}
	map->height = get_line_count(file, map);
	alloc_grid(map, fd);
	read_lines(map, fd, file);
	close(fd);
}
