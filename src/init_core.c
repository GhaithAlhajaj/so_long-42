/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:36:20 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 21:57:00 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	*safe_alloc(size_t size)
{
	void	*mem;

	if (size == 0)
	{
		ft_printf("Error: Attempted to allocate 0 bytes.\n");
		exit(EXIT_FAILURE);
	}
	mem = malloc(size);
	if (!mem)
	{
		ft_printf("Error: Memory allocation failed (size: %d bytes).\n",
			(int)size);
		exit(EXIT_FAILURE);
	}
	return (mem);
}

int	open_level(const char *path, t_map *map)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		free(map);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
