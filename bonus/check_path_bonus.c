/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:43:20 by noaziki           #+#    #+#             */
/*   Updated: 2025/03/01 11:46:08 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	flood_fill(char **map, int x, int y)
{
	if (map[x][y] == '1' || map[x][y] == 'A'
		|| map[x][y] == 'E' || map[x][y] == 'N')
		return ;
	if (map[x][y] == '0' || map[x][y] == 'C')
		map[x][y] = 'A';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void	position(t_game *game, char c)
{
	game->i = 0;
	while (game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			if (game->map[game->i][game->j] == c)
			{
				game->player_x = game->i;
				game->player_y = game->j;
			}
			game->j++;
		}
		game->i++;
	}
}

int	check_exit(t_game *game)
{
	position(game, 'E');
	if (game->map2[game->player_x + 1][game->player_y] == 'A'
	|| game->map2[game->player_x - 1][game->player_y] == 'A'
	|| game->map2[game->player_x][game->player_y + 1] == 'A'
	|| game->map2[game->player_x][game->player_y - 1] == 'A')
		return (0);
	return (1);
}

int	check_path(t_game *game, char *filename)
{
	int		lines;

	game->enemy_y = 0;
	game->enemy_x1 = 0;
	game->enemy_x2 = 0;
	lines = count_lines(filename, game);
	position(game, 'P');
	game->map2 = malloc((lines + 1) * sizeof(char *));
	if (!game->map2)
		print_error("Error\nMemory allocation failed for map!\n", game);
	read_map(filename, game, game->map2);
	flood_fill(game->map2, game->player_x, game->player_y);
	if (check_content(game, game->map2, "01PAE") || check_exit(game))
		return (free_game(game->map2), 1);
	free_game(game->map2);
	initialize_enemy(game);
	check_enemy_path(game, filename);
	return (0);
}
