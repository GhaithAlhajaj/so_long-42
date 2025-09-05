/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galhajaj <galhajaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:36:20 by galhajaj          #+#    #+#             */
/*   Updated: 2025/04/22 21:35:32 by galhajaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 60
# define TEXTURE_COUNT 10
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/keysym.h>
# include "../libft/libft.h"

typedef struct s_map
{
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		door_x;
	int		door_y;
	int		collectibles;
	int		moves;
	int		exit_flag;
	char	**grid;
	char	last_tile;

}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*tex[10];
	int		tex_width;
	int		tex_height;
	t_map	*map;
}	t_game;

typedef struct s_dfs_data
{
	char	**grid;
	int		width;
	int		height;
	int		*collect;
	int		*exit;
}	t_dfs_data;

int		open_level(const char *path, t_map *map);
void	read_map(t_map *map, const char *file);
int		check_layout(t_map *map);
int		valid_shape(t_map *map);
int		valid_path(t_map *map);
void	draw_world(t_game *game);
int		update_frame(t_game *game);
int		manage_key(int key, t_game *game);
void	execute_move(t_game *game, int dx, int dy, char move);
int		close_game(t_game *game);
void	*safe_alloc(size_t size);
void	free_grid(char **grid, int height);
void	free_game(t_game *game);
int		check_border(t_map *map);
int		chk_format(int argc, char *map_name);
void	update_player_position(t_game *game, int dx, int dy, char move);

#endif
